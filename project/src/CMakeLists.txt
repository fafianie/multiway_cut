cmake_minimum_required(VERSION 3.5.2)
set (CMAKE_CXX_STANDARD 11)
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
	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/cplex"
	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/cplex/include/ilcplex")
add_library(concert SHARED IMPORTED)
set_target_properties(concert PROPERTIES 
	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/concert"
	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/concert/include/ilconcert")

add_subdirectory(solvers)
#if (NOT CPLEX)
#	message("could not find CPLEX")
#elseif (NOT CONCERT)
#	message("could not find CONCERT")
#else()
#	add_subdirectory(solvers)
#endif()