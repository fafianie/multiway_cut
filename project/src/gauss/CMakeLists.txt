set(SOURCES
	src/gauss.cpp)
	
add_library(gauss STATIC ${SOURCES})
target_link_libraries(gauss matroids galois stdafx)
target_include_directories(gauss PUBLIC ./src)

add_executable(gaussian_elimination_test test/gaussian_elimination_test.cpp)
target_link_libraries(gaussian_elimination_test gauss matroids galois stdafx)
add_test(GaussianEliminationWorks gaussian_elimination_test)