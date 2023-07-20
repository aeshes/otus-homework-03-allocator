cmake_minimum_required(VERSION 3.5)

project(test)

enable_testing()

add_executable(test map_test.cpp)

set_target_properties(test PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(test
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(
	test
	GTest::gtest_main
)
