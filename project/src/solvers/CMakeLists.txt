target_include_directories(solvers PUBLIC ./src)

add_executable(dummy_test test/dummy_test.cpp)
target_link_libraries(dummy_test stdafx)
add_test(DummyTests dummy_test)

add_executable(blend test/blend.cpp) 
target_link_libraries(blend stdafx)
add_test(BlendWorks blend)