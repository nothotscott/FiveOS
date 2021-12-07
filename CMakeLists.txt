
project(FiveOS C ASM)
cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)
set(LIBC "pdclib")
set(CROSS_COMPILE "/opt/riscv32/bin/riscv32-unknown-elf-")
set(STACK_SIZE 0xf00)
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/link.lds")

set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}as)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)

set(CMAKE_GENERAL_FLAGS "-g -Wall -ffunction-sections -march=rv32imac")
set(CMAKE_C_FLAGS "${CMAKE_GENERAL_FLAGS} -Os" CACHE STRING "")
set(CMAKE_ASM_FLAGS "${CMAKE_GENERAL_FLAGS}" CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -fno-exceptions -Xlinker --defsym=__stack_size=${STACK_SIZE} -T ${LINKER_SCRIPT}")

# Compile
include_directories(sdk/${LIBC}/include)
include_directories(sdk/${LIBC}/platform/include)
include_directories(sdk/include)
# add_subdirectory(sdk/${LIBC})

# add_subdirectory(boot)
add_subdirectory(fivekrnl)

# Link
add_executable(fiveos.elf)
target_link_libraries(fiveos.elf kernel)
set_target_properties(fiveos.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})