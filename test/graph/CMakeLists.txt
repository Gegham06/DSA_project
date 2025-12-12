# Create the test executable
add_executable(
    graph_tests
    test_runner.c
    test_algorithms.c
    test_graph_operations.c
)

# Link the test executable against your library
target_link_libraries(graph_tests PRIVATE dsalib)

# Add the test to CTest
add_test(
    NAME graph_tests
    COMMAND graph_tests
)
