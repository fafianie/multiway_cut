if(NOT CPLEX_LIBRARY)
	return()
endif()

set(SOURCES
	src/multiway_cut_solver.cpp
	src/multiway_cut_relaxation_solver.cpp
	src/blend.cpp)
	
add_library(solvers STATIC ${SOURCES})
target_link_libraries(solvers graphs ilocplex stdafx)
target_include_directories(solvers PUBLIC ./src)

add_executable(correctness_test test/correctness_test.cpp)
target_link_libraries(correctness_test graphs readers solvers ilocplex stdafx)
#add_test(MWCSolverIsCorrect correctness_test)

add_executable(blend test/blend_test.cpp) 
target_link_libraries(blend ilocplex stdafx)
add_test(BlendWorks blend)