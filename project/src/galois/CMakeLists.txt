set(SOURCES 
	src/galois.cpp
	src/naive_galois.cpp
	src/carryless_multiplier_galois.cpp
	src/table_galois.cpp
	src/logarithm_table_galois.cpp)

add_library(galois STATIC ${SOURCES})
target_link_libraries(galois stdafx constants)
target_include_directories(galois PUBLIC ./src)

add_executable(carryless_multiplier_test test/carryless_multiplier_test.cpp)
target_link_libraries(carryless_multiplier_test galois stdafx constants)
add_test(CarrylessMultiplierWorks carryless_multiplier_test)

add_executable(logarithm_table_test test/logarithm_table_test.cpp)
target_link_libraries(logarithm_table_test galois stdafx constants)
add_test(LogarithmTableGaloisWorks logarithm_table_test)