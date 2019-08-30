set(SOURCES
	src/dgf_writer.cpp)
	
add_library(writers STATIC ${SOURCES})
target_link_libraries(writers graphs stdafx)
target_include_directories(writers PUBLIC ./src)

add_executable(dgf_writer_test test/dgf_writer_test.cpp)
target_link_libraries(dgf_writer_test readers writers graphs stdafx)
add_test(DGFWriterWorks dgf_writer_test)