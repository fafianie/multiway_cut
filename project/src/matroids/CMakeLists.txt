set(SOURCES
	src/matroid.cpp
	src/uniform_matroid.cpp)
	
add_library(matroids STATIC ${SOURCES})
target_link_libraries(matroids galois stdafx)
target_include_directories(matroids PUBLIC ./src)

add_executable(matroid_dummy_test test/matroid_dummy_test.cpp)
target_link_libraries(matroid_dummy_test matroids stdafx)
add_test(MatroidDummyWorks matroid_dummy_test)

add_executable(uniform_matroid_test test/uniform_matroid_test.cpp)
target_link_libraries(uniform_matroid_test galois matroids stdafx)
add_test(UniformMatroidWorks uniform_matroid_test)