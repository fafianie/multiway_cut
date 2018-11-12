set(SOURCES
	src/matroid.cpp)
	
add_library(matroids STATIC ${SOURCES})
target_link_libraries(matroids stdafx)
target_include_directories(matroids PUBLIC ./src)

add_executable(matroid_dummy_test test/matroid_dummy_test.cpp)
target_link_libraries(matroid_dummy_test matroids stdafx)
add_test(MatroidDummyWorks matroid_dummy_test)