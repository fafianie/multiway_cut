add_library(constants STATIC src/primitives.cpp src/powers.cpp)
target_link_libraries(constants stdafx)
target_include_directories(stdafx PUBLIC ./src)