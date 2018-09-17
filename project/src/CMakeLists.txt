cmake_minimum_required(VERSION 3.6.2)
project(multiwaycut)
enable_language(C ASM)

enable_testing()
add_subdirectory(main)
add_subdirectory(stdafx)
add_subdirectory(constants)
add_subdirectory(galois)