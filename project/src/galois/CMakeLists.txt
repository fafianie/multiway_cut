add_library(igalois STATIC src/igalois.cpp src/naive_galois.cpp src/carryless_multiplier_galois.cpp src/table_galois.cpp src/logarithm_table_galois.cpp)
target_link_libraries(igalois stdafx constants)
target_include_directories(igalois PUBLIC ./src)

add_executable(pcmul_test test/pcmul_test.cpp)
target_link_libraries(pcmul_test igalois stdafx constants)
add_test(TestWorks pcmul_test)

add_executable(logarithm_table_test test/logarithm_table_test.cpp)
target_link_libraries(logarithm_table_test igalois stdafx constants)
add_test(LogarithmTableGaloisWorks logarithm_table_test)