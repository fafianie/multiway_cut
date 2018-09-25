set(SOURCES 
	src/igalois.cpp
	src/naive_galois.cpp
	src/carryless_multiplier_galois.cpp
	src/table_galois.cpp
	src/logarithm_table_galois.cpp)

add_library(igalois STATIC ${SOURCES})
target_link_libraries(igalois stdafx constants)
target_include_directories(igalois PUBLIC ./src)

add_executable(carryless_multiplier_test test/carryless_multiplier_test.cpp)
target_link_libraries(carryless_multiplier_test igalois stdafx constants)
add_test(CarrylessMultiplierWorks carryless_multiplier_test)

add_executable(logarithm_table_test test/logarithm_table_test.cpp)
target_link_libraries(logarithm_table_test igalois stdafx constants)
add_test(LogarithmTableGaloisWorks logarithm_table_test)