add_executable(main src/main.cpp)
target_link_libraries(main constants stdafx)

if (CPLEX_LIBRARY)
	add_executable(instance_generation src/instance_generation.cpp)
	target_link_libraries(instance_generation writers solvers graphs stdafx)
endif()