set(TEST_NAME TESTING)
AUX_SOURCE_DIRECTORY(./src ${TEST_NAME}_SRCS)
add_executable(${TEST_NAME}
    ${${TEST_NAME}_SRCS}
)
target_link_libraries(${TEST_NAME} 
    s21_graph    
    s21_graph_algorithms
    gtest
)
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
add_test(NAME TestMyCode COMMAND TestMyCode)
