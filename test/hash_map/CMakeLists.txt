# Create the test executable
add_executable(
    hash_map_tests
    test_hash_map.c
)

# Link the test executable against your library
target_link_libraries(hash_map_tests PRIVATE dsalib)

# Add the test to CTest
add_test(
    NAME hash_map_tests
    COMMAND hash_map_tests
)
