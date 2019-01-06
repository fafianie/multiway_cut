include(FindCPLEX.cmake)

if(NOT CPLEX_LIBRARY)
	return()
endif()

set(SOURCES
	src/lpsolver.cpp
	src/mwcsolver.cpp
	src/blend.cpp)
	
add_library(solvers STATIC ${SOURCES})
target_link_libraries(solvers ilocplex stdafx)
target_include_directories(solvers PUBLIC ./src)

add_executable(correctness_test test/correctness_test.cpp)
target_link_libraries(correctness_test graphs solvers ilocplex stdafx)
add_test(MWCSolverIsCorrect correctness_test)

add_executable(blend test/blend_test.cpp) 
target_link_libraries(blend ilocplex stdafx)
add_test(BlendWorks blend)