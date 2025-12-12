# Create the test executable
add_executable(
    vector_tests
    vector_test.c
)

# Link the test executable against your library
target_link_libraries(vector_tests PRIVATE dsalib)

# Add the test to CTest
add_test(
    NAME vector_tests
    COMMAND vector_tests
)
