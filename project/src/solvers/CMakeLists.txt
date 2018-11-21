include(FindCPLEX.cmake)
set(SOURCES
	src/blend.cpp)

if(CPLEX_LIBRARY)
	message("CPLEX WAS FOUND") 
endif()
	
add_library(solvers STATIC ${SOURCES})
target_link_libraries(solvers ilocplex stdafx)
target_include_directories(solvers PUBLIC ./src)

add_executable(dummy_test test/dummy_test.cpp)
target_link_libraries(dummy_test stdafx)
add_test(DummyTests dummy_test)

add_executable(blend test/blend_test.cpp) 
target_link_libraries(blend ilocplex stdafx)
add_test(BlendWorks blend)