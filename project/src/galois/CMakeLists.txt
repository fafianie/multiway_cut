enable_language(C ASM)
#set_source_files_properties(src/pclmul.asm PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp" )
#set_property(SOURCE src/pclmul.asm PROPERTY LANGUAGE C)
#target_include_directories(pclmul PUBLIC ./src)

#TODO: FIGURE OUT THIS STUFF IN MAKE FIRST, THEN CMAKE, THEN VISUAL STUDIO 
#add_executable(asm src/pclmul.s)


add_library(galois STATIC src/galois.cpp)
target_link_libraries(galois stdafx constants)

target_include_directories(galois PUBLIC ./src)


add_executable(pcmul_test test/pcmul_test.cpp)
target_link_libraries(pcmul_test galois stdafx constants)
add_test(TestWorks pcmul_test)


#TODO: split galois into interface and implementations