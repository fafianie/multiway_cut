set(SOURCES
	src/dfg_reader.cpp)
	
add_library(readers STATIC ${SOURCES})
target_link_libraries(readers graphs stdafx)
target_include_directories(readers PUBLIC ./src)

add_executable(reader_dummy_test test/reader_dummy_test.cpp)
target_link_libraries(reader_dummy_test readers graphs stdafx)
add_test(ReaderDummyWorks reader_dummy_test)