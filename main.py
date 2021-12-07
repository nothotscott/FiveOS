#!/usr/bin/env python3
# PROJECT:     FiveOS Build
# LICENSE:     LGPL-3.0-or-later (https://spdx.org/licenses/LGPL-3.0-or-later.html)
# PURPOSE:     Native compatibility for windows, so long as it's invoked on the WSL UNC path
# COPYRIGHT:   Copyright 2021 Scott Maday <coldasdryice1@gmail.com>

import os, sys, subprocess

if __name__ == "__main__":
	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	if sys.platform == "win32":
		print("Switching to WSL")
		subprocess.run(["wsl", "python3", "build.py"] + sys.argv[1:])
	else:
		import build
		build.main()
