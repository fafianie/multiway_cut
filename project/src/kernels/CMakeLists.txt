set(SOURCES
	src/multiway_cut_kernel.cpp)
	
add_library(kernels STATIC ${SOURCES})
target_link_libraries(kernels galois matroids graphs stdafx)
target_include_directories(kernels PUBLIC ./src)

if(NOT CPLEX_LIBRARY)
	return()
endif()

#add_executable(correctness_test test/correctness_test.cpp)
#target_link_libraries(correctness_test graphs readers solvers ilocplex stdafx)
#add_test(MWCSolverIsCorrect correctness_test)
