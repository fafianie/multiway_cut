cmake_minimum_required(VERSION 3.5.2)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD")
project(multiwaycut)

enable_testing()
add_subdirectory(main)
add_subdirectory(stdafx)
add_subdirectory(constants)
add_subdirectory(galois)
add_subdirectory(gauss)
add_subdirectory(matroids)
add_subdirectory(graphs)
add_subdirectory(readers)

add_library(cplex SHARED IMPORTED)
set_target_properties(cplex PROPERTIES
	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/cplex/lib/x86-64_linux/static_pic/cplex.a"
	INTERFACE_INCLUDE_DIRECTORIES "opt/ibm/ILOG/CPLEX_Studio128/cplex/include")
add_library(ilocplex SHARED IMPORTED)
set_target_properties(ilocplex PROPERTIES 
	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/cplex/lib/x86-64_linux/static_pic/ilocplex.a"
	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/cplex/include")
target_link_libraries(ilocplex cplex)
add_library(concert SHARED IMPORTED)
set_target_properties(concert PROPERTIES 
	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/concert/lib/x86-64_linux/static_pic"
	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/concert/include")

#IDEAS: add other .a files somehow
#		use find_library instead (USE HINTS)
	
add_subdirectory(solvers)
#if (NOT CPLEX)
#	message("could not find CPLEX")
#elseif (NOT CONCERT)
#	message("could not find CONCERT")
#else()
#	add_subdirectory(solvers)
#endif()