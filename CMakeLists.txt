
project(FiveOS C ASM)
cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)
set(LIBC "pdclib")
set(CMAKE_SYSTEM_PROCESSOR "rv32imac")
find_file(CROSS_COMPILE "riscv32-unknown-elf-gcc")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/link.lds")

string(REGEX REPLACE "\-gcc" "-" CROSS_COMPILE ${CROSS_COMPILE})
set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)

message(STATUS "RISC-V Compiler:  ${CMAKE_C_COMPILER}")
message(STATUS "RISC-V Assembler: ${CMAKE_ASM_COMPILER}")

set(FIVEOS_GENERAL_FLAGS "-g -Wall -ffunction-sections -ffreestanding -march=${CMAKE_SYSTEM_PROCESSOR} -Wl,--export-dynamic -mcpu=sifive-e31 -mabi=ilp32 -static -mcmodel=medany")
set(FIVEOS_C_ONLY_FLAGS "")

set(CMAKE_C_FLAGS "${FIVEOS_GENERAL_FLAGS} ${FIVEOS_C_ONLY_FLAGS}")
set(CMAKE_ASM_FLAGS "${FIVEOS_GENERAL_FLAGS}")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -nostdlib -fno-exceptions -Xlinker -T ${LINKER_SCRIPT}")

# Compile
include_directories(sdk/${LIBC}/include)
include_directories(sdk/${LIBC}/platform/include)
include_directories(sdk/include)
# add_subdirectory(sdk/${LIBC})

add_subdirectory(boot)
add_subdirectory(fivekrnl)

# Link
add_executable(fiveos.elf)
target_link_libraries(fiveos.elf kernel boot)
set_target_properties(fiveos.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
