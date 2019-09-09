set(SOURCES
	src/independent_set.cpp)
	
add_library(gauss STATIC ${SOURCES})
target_link_libraries(gauss matroids galois stdafx)
target_include_directories(gauss PUBLIC ./src)