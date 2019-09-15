set(SOURCES
	src/multiway_cut_kernel.cpp)
#set(LIBRARIES
#	galois solvers matroids graph stdafx)
	
#if(CPLEX_LIBRARY)
#	set(SOURCES ${SOURCES}
#		src/half_integral_reduction.cpp)
#	set(LIBRARIES ${LIBRARIES}
#		solvers)
#endif()

add_library(kernels STATIC ${SOURCES})
target_link_libraries(kernels galois solvers matroids graph stdafx)
target_include_directories(kernels PUBLIC ./src)

if(NOT CPLEX_LIBRARY)
	return()
endif()


add_executable(multiway_cut_kernel_test test/multiway_cut_kernel_test.cpp)
target_link_libraries(multiway_cut_kernel_test graphs readers writers solvers kernels galois stdafx)
#add_test(MCWKernelIsCorrect multiway_cut_kernel_test)





#add_executable(correctness_test test/correctness_test.cpp)
#target_link_libraries(correctness_test graphs readers solvers ilocplex stdafx)
#add_test(MWCSolverIsCorrect correctness_test)
