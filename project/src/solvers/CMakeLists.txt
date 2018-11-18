set(SOURCES
	src/blend.cpp)
	
add_library(solvers STATIC ${SOURCES})
target_link_libraries(solvers cplex concert stdafx)
target_include_directories(solvers PUBLIC ./src)

add_executable(dummy_test test/dummy_test.cpp)
target_link_libraries(dummy_test stdafx)
add_test(DummyTests dummy_test)

add_executable(blend test/blend_test.cpp) 
target_link_libraries(blend cplex concert stdafx)
add_test(BlendWorks blend)