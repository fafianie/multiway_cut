set(SOURCES
	src/graph.cpp
	src/decorated_graph.cpp
	src/planted_instance.cpp)
	
add_library(graphs STATIC ${SOURCES})
target_link_libraries(graphs stdafx)
target_include_directories(graphs PUBLIC ./src)

add_executable(graph_operations_test test/graph_operations_test.cpp)
target_link_libraries(graph_operations_test graphs stdafx)
add_test(GraphOperationsWorks graph_operations_test)

add_executable(decorated_graph_test test/decorated_graph_test.cpp)
target_link_libraries(decorated_graph_test graphs stdafx)
add_test(DecoratedGraphWorks decorated_graph_test)