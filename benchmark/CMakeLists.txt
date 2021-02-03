file(GLOB SRC_BENCHMARK_FILES
	"*.cpp"
)

add_executable(effective_lru-benchmark
        ${SRC_BENCHMARK_FILES}
)

include_directories(../include/)

#add_test(NAME effective_lru-benchmark COMMAND effective_lru-benchmark)

target_link_libraries(effective_lru-benchmark PUBLIC effective_lru-static benchmark::benchmark)
