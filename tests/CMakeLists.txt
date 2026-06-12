add_executable(check
    test_account.cpp
    test_transaction.cpp
)

target_link_libraries(check
    banking
    gtest_main
    gmock
)

if(COLLECT_COVERAGE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(check --coverage)
endif()

add_test(NAME check COMMAND check)
