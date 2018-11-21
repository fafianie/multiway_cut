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
add_subdirectory(solvers)

#set(CPLEX_ILOG_DIR /opt/ibm/ILOG)
#set(CPLEX_ARCH x86_64)
#set(CPLEX_LIB_PATH_SUFFIXES	lib/${CPLEX_ARCH}_linux/static_pic)


#find_package(Threads)

#set(CPLEX_DIR ${CPLEX_ILOG_DIR}/CPLEX_Studio128/cplex)
#set(CPLEX_INCLUDE_DIR ${CPLEX_DIR}/include)
#set(CPLEX_LINK_LIBRARIES ${CPLEX_DIR}/${CPLEX_LIB_PATH_SUFFIXES})
#find_library(CPLEX_LIBRARY 
#	NAMES cplex
#	PATHS ${CPLEX_DIR}
#	PATH_SUFFIXES ${CPLEX_LIB_PATH_SUFFIXES})

#add_library(cplex STATIC IMPORTED GLOBAL)
#set_target_properties(cplex PROPERTIES
#    IMPORTED_LOCATION "${CPLEX_LIBRARY}"
#    IMPORTED_LOCATION_DEBUG "${CPLEX_LIBRARY}"
#    INTERFACE_INCLUDE_DIRECTORIES "${CPLEX_INCLUDE_DIR}"
#    INTERFACE_LINK_LIBRARIES "${CPLEX_LINK_LIBRARIES}")

#set(CONCERT_DIR ${CPLEX_ILOG_DIR}/CPLEX_Studio128/concert)
#set(CONCERT_INCLUDE_DIR ${CONCERT_DIR}/include)
#set(CONCERT_LINK_LIBRARIES ${CONCERT_DIR}/${CPLEX_LIB_PATH_SUFFIXES})
#find_library(CONCERT_LIBRARY
#	NAMES concert
#	PATHS ${CONCERT_DIR}
#	PATH_SUFFIXES ${CPLEX_LIB_PATH_SUFFIXES})
#add_library(concert STATIC IMPORTED GLOBAL)
#set_target_properties(concert PROPERTIES
#	IMPORTED_LOCATION "${CONCERT_LIBRARY}"
#	IMPORTED_LOCATION_DEBUG "${CONCERT_LIBRARY}"
#	INTERFACE_INCLUDE_DIRECTORIES "${CONCERT_INCLUDE_DIR}"
 #   INTERFACE_LINK_LIBRARIES "${CONCERT_LINK_LIBRARIES}"
	
#find_library(ILOCPLEX_LIBRARY
#	NAMES ilocplex
#	PATHS ${CPLEX_DIR}
#	PATH_SUFFIXES ${CPLEX_LIB_PATH_SUFFIXES})
#add_library(ilocplex STATIC IMPORTED GLOBAL)
#set_target_properties(ilocplex PROPERTIES
#	IMPORTED_LOCATION "${CPLEX_LIBRARY}"
#	IMPORTED_LOCATION_DEBUG "${CPLEX_LIBRARY}"
#	INTERFACE_INCLUDE_DIRECTORIES "${CPLEX_INCLUDE_DIR}"
 #   INTERFACE_LINK_LIBRARIES "${CPLEX_LINK_LIBRARIES}"
	



#add_library(cplexdistmip SHARED IMPORTED)
#set_target_properties(cplexdistmip PROPERTIES
#	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/cplex/lib/x86-64_linux/static_pic/libcplexdistmip.a"
#	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/cplex/include")
#add_library(cplex SHARED IMPORTED)
#set_target_properties(cplex PROPERTIES
#	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/cplex/lib/x86-64_linux/static_pic/libcplex.a"
#	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/cplex/include")
#add_library(ilocplex SHARED IMPORTED)
#set_target_properties(ilocplex PROPERTIES 
#	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/cplex/lib/x86-64_linux/static_pic/libilocplex.a"
#	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/cplex/include")
#target_link_libraries(ilocplex cplex)
#add_library(concert SHARED IMPORTED)
#set_target_properties(concert PROPERTIES 
#	IMPORTED_LOCATION "/opt/ibm/ILOG/CPLEX_Studio128/concert/lib/x86-64_linux/static_pic/libconcert.a"
#	INTERFACE_INCLUDE_DIRECTORIES "/opt/ibm/ILOG/CPLEX_Studio128/concert/include")

#IDEAS: add other .a files somehow
#		use find_library instead (USE HINTS)
	

#if (NOT CPLEX)
#	message("could not find CPLEX")
#elseif (NOT CONCERT)
#	message("could not find CONCERT")
#else()
#	add_subdirectory(solvers)
#endif()