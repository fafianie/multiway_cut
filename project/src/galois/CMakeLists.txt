enable_language(ASM)
set_source_files_properties(pclmul.asm PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp" )
#target_include_directories(pclmul PUBLIC ./src)


add_library(galois STATIC src/galois.cpp src/pclmul.asm)
target_link_libraries(galois stdafx constants)

target_include_directories(galois PUBLIC ./src)


#add_executable(pcmul_test test/pcmul_test.cpp)
#target_link_libraries(pcmul_test stdafx galois)
#add_test(TestWorks pcmul_test)


#TODO: split galois into interface and implementations