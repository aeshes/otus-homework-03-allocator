cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

project(testing)

add_executable(tests vector_test.cpp list_test.cpp map_test.cpp)

set_target_properties(tests PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(tests
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(
        tests
	GTest::gtest_main
)

include(CTest)

add_test(NAME tests COMMAND tests)
