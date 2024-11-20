# Define the tests
set(TEST_SOURCES
    TestModels.cpp
    TestMonteCarlo.cpp
    TestBlackModel.cpp
    TestBinomialTreeModel.cpp
    TestFiniteDifferenceMethod.cpp
)

# Add the test executable
add_executable(run_tests ${TEST_SOURCES})

# Link the Google Test library and our source library
target_link_libraries(run_tests PRIVATE 
    swaption_lib
    GTest::GTest 
    GTest::Main 
    pthread
)

# Register the tests
add_test(NAME run_tests COMMAND run_tests)
