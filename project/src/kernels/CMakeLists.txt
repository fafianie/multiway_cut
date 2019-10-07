set(SOURCES
 	src/multiway_cut_kernel.cpp
	)

if(CPLEX_LIBRARY)
	set (SOURCES 
		${SOURCES}
		src/half_integral_reduction.cpp
		)
endif()

add_library(kernels STATIC ${SOURCES})
target_link_libraries(kernels galois matroids solvers graphs stdafx)
target_include_directories(kernels PUBLIC ./src)

if (NOT CPLEX_LIBRARY)
	return()
endif()

add_executable(multiway_cut_kernel_test test/multiway_cut_kernel_test.cpp)
target_link_libraries(multiway_cut_kernel_test graphs readers writers solvers kernels galois stdafx)
#add_test(MCWKernelIsCorrect multiway_cut_kernel_test)

add_executable(half_integral_reduction_test test/half_integral_reduction_test.cpp)
target_link_libraries(half_integral_reduction_test graphs readers solvers kernels stdafx)
#add_test(HalfIntegralReductionIsCorrect half_integral_reduction_test)
 


#add_executable(correctness_test test/correctness_test.cpp)
#target_link_libraries(correctness_test graphs readers solvers ilocplex stdafx)

