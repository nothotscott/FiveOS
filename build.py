# PROJECT:     FiveOS Build
# LICENSE:     LGPL-3.0-or-later (https://spdx.org/licenses/LGPL-3.0-or-later.html)
# PURPOSE:     Primary build functions
# COPYRIGHT:   Copyright 2021 Scott Maday <coldasdryice1@gmail.com>

import os, sys, logging, subprocess
import multiprocessing
from platform import uname
from optparse import OptionParser

# Main configuration
OSNAME			= "FiveOS"
OUTPUT_DIR		= "output-rv32i"
DEFAULT_TASKS	= []
CMAKE_VARS		= []
# Qemu configuration
QEMU_MEMORY		= "512M"
QEMU_CORES		= 1
QEMU_MISC		= "-machine sifive_u -net none -nographic"

is_wsl = "Microsoft" in uname().release
logger = logging.getLogger()
debug = False

### System functions ###

def host_path_absolute(path):
	abs_path = os.path.abspath(path)
	if is_wsl:
		completed_proc = subprocess.run(["wslpath", "-w", abs_path], capture_output=True)
		return completed_proc.stdout.decode("utf-8")[:-1]	# chop off newline
	else:
		return abs_path

def execute(command, exit_if_failed = True):
	results = os.system(command)
	if exit_if_failed and results != 0:
		logger.critical("Error occurred when executing the task: {}\nCode: {}".format(command, results))
		sys.exit(results)

### Tasks ###

def build(target=None):
	jobs = max(1, multiprocessing.cpu_count())
	cmake_vars = CMAKE_VARS
	cmake_vars += ["CMAKE_BUILD_TYPE={}".format("Debug" if debug else "Release")]
	if not os.path.exists(OUTPUT_DIR):
		logger.info("Creating output directory")
		os.mkdir(OUTPUT_DIR)
	execute("cd {} && cmake ../ -GNinja {}".format(OUTPUT_DIR, " ".join(["-D" + var for var in cmake_vars])))
	execute("cd {} && ninja {} -j{}".format(OUTPUT_DIR, "" if target == None else target, jobs))


def run_qemu():
	kernel_path = os.path.join(OUTPUT_DIR, "{}.elf".format(OSNAME))
	if not os.path.exists(kernel_path):
		logger.warning("No kernel found before running. Getting now.")
		build("fiveos.elf")
	qemu = "qemu-system-riscv32{}".format(".exe" if is_wsl else "")
	args = ["-kernel", kernel_path]
	args += ["-smp", str(QEMU_CORES), "-m", QEMU_MEMORY]
	args += QEMU_MISC.split(" ")
	if debug:
		args += ["-s", "-S"]
		if is_wsl:
			subprocess.run("powershell.exe 'Start-Process {} -ArgumentList \"{}\"'".format(qemu, " ".join(args)), shell=True)
		else:
			command = " ".join([qemu] + args)
			subprocess.Popen(command, stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
	else:
		subprocess.run([qemu] + args)


### Main ###

def main():
	global debug, toolchain
	logging.basicConfig(level=logging.DEBUG)

	parser = OptionParser()
	parser.add_option("-d", "--debug", action="store_true", default=True, help="Enables debug mode")
	parser.add_option("-b", "--build", action="store_true", help="Builds the FiveOS Kernel")
	parser.add_option("-r", "--run", action="store_true", help="Runs FiveOS in qemu")
	options, _ = parser.parse_args()
	if len(sys.argv) <= 1:
		for task in DEFAULT_TASKS:
			setattr(options, task, True)

	debug = options.debug
	if options.build:
		build("fiveos.elf")
	if options.run:
		run_qemu()

if __name__ == "__main__":
	main()