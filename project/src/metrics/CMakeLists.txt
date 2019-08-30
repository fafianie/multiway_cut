set(SOURCES
	src/metrics.cpp)
	
add_library(metrics STATIC ${SOURCES})
target_link_libraries(metrics stdafx)
target_include_directories(metrics PUBLIC ./src)