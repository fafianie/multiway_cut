set(SOURCES 
	src/galois.cpp
	src/naive_galois.cpp
	src/carryless_multiplier_galois.cpp
	src/table_galois.cpp
	src/logarithm_table_galois.cpp)

add_library(galois STATIC ${SOURCES})
target_link_libraries(galois stdafx constants)
target_include_directories(galois PUBLIC ./src)



add_executable(inversion_test test/inversion_test.cpp)
target_link_libraries(inversion_test galois stdafx)
add_test(InversionWorks inversion_test)

add_executable(table_test test/table_test.cpp)
target_link_libraries(table_test galois stdafx)
add_test(TableGaloisWorks table_test)

add_executable(logarithm_table_test test/logarithm_table_test.cpp)
target_link_libraries(logarithm_table_test galois stdafx)
add_test(LogarithmTableGaloisWorks logarithm_table_test)

add_executable(carryless_multiplier_test test/carryless_multiplier_test.cpp)
target_link_libraries(carryless_multiplier_test galois stdafx)
add_test(CarrylessMultiplierWorks carryless_multiplier_test)