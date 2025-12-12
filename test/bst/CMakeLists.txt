# Create the test executable
add_executable(
    bst_tests
    test_binary_search_tree.c
)

# Link the test executable against your library
target_link_libraries(bst_tests PRIVATE dsalib)

# Add the test to CTest
add_test(
    NAME bst_tests
    COMMAND bst_tests
)
