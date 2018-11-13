set(SOURCES
	src/graph.cpp)
	
add_library(graphs STATIC ${SOURCES})
target_link_libraries(graphs stdafx)
target_include_directories(graphs PUBLIC ./src)

add_executable(graph_dummy_test test/graph_dummy_test.cpp)
target_link_libraries(graph_dummy_test graphs stdafx)
add_test(GraphDummyWorks graph_dummy_test)