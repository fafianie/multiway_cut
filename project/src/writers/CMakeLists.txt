set(SOURCES
	src/dgf_writer.cpp
	src/metrics_writer.cpp)
	
add_library(writers STATIC ${SOURCES})
target_link_libraries(writers graphs metrics stdafx)
target_include_directories(writers PUBLIC ./src)

add_executable(dgf_writer_test test/dgf_writer_test.cpp)
target_link_libraries(dgf_writer_test readers writers graphs stdafx)
add_test(DGFWriterWorks dgf_writer_test)

add_executable(metrics_writer_test test/metrics_writer_test.cpp)
target_link_libraries(metrics_writer_test metrics writers stdafx)
add_test(MetricsWriterWorks metrics_writer_test)