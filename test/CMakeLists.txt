file(GLOB SRC_TEST_FILES
	"*.cpp"
)

add_executable(effective_lru-test
	${SRC_TEST_FILES}
)

include_directories(../include/)

add_test(NAME effective_lru-test COMMAND iec_time_converter-test)

target_link_libraries(effective_lru-test PUBLIC effective_lru-static gtest pthread)
