set(SOURCES
	src/matroid.cpp
	src/uniform_matroid.cpp
	src/transversal_matroid.cpp
	src/dual_matroid.cpp
	src/gammoid.cpp)
	
add_library(matroids STATIC ${SOURCES})
target_link_libraries(matroids graphs galois gauss stdafx)
target_include_directories(matroids PUBLIC ./src)

add_executable(matroid_copy_constructor_test test/matroid_copy_constructor_test.cpp)
target_link_libraries(matroid_copy_constructor_test matroids stdafx)
add_test(MatroidCopyConstructorWorks matroid_copy_constructor_test)

add_executable(uniform_matroid_test test/uniform_matroid_test.cpp)
target_link_libraries(uniform_matroid_test gauss galois matroids constants stdafx)
add_test(UniformMatroidWorks uniform_matroid_test)

add_executable(transversal_matroid_test test/transversal_matroid_test.cpp)
target_link_libraries(transversal_matroid_test gauss galois matroids stdafx)
add_test(TransversalMatroidWorks transversal_matroid_test)

add_executable(gammoid_test test/gammoid_test.cpp)
target_link_libraries(gammoid_test gauss galois matroids stdafx)
add_test(GammoidWorks gammoid_test)