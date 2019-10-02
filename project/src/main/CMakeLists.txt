add_executable(main src/main.cpp)
target_link_libraries(main constants stdafx)

add_executable(timeout src/timeout.cpp) 
target_link_libraries(timeout stdafx)

add_executable(memory src/memory.cpp)
target_link_libraries(memory galois stdafx)

if (CPLEX_LIBRARY)
	add_executable(instance_generation src/instance_generation.cpp)
	target_link_libraries(instance_generation writers solvers graphs stdafx)
endif()