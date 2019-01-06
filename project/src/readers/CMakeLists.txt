set(SOURCES
	src/dgf_reader.cpp)
	
add_library(readers STATIC ${SOURCES})
target_link_libraries(readers graphs stdafx)
target_include_directories(readers PUBLIC ./src)

add_executable(dgf_reader_test test/dgf_reader_test.cpp)
target_link_libraries(dgf_reader_test readers graphs stdafx)
add_test(DGFReaderWorks dgf_reader_test)