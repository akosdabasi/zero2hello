#defines the type of platform tageted: Linux, Android... Generic for bare-metal
set(CMAKE_SYSTEM_NAME               Generic)

#specifies the target architecture
set(CMAKE_SYSTEM_PROCESSOR          arm)

#custom variables for convenience
set(toolchain_prefix                arm-none-eabi-)
set(tools_path                      "C:/Dev/tools")
set(toolchain_path                  ${tools_path}/gcc-arm-none-eabi/bin)

# Define compiler settings
set(CMAKE_C_COMPILER                ${toolchain_path}/${toolchain_prefix}gcc.exe)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${toolchain_path}/${toolchain_prefix}g++.exe)
set(CMAKE_OBJCOPY                   ${toolchain_path}/${toolchain_prefix}objcopy.exe)
set(CMAKE_SIZE                      ${toolchain_path}/${toolchain_prefix}size.exe)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

#for making compiler checks pass
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)