cmake_minimum_required(VERSION 3.10)

project(lab05tut)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)
option(COLLECT_COVERAGE "Collect coverage" OFF)

if(COLLECT_COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)

install(TARGETS formatter formatter_ex solver hello_world equation
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

if(BUILD_TESTS)
    enable_testing()

    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(third-party/gtest)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        foreach(_target gtest gtest_main gmock gmock_main)
            if(TARGET ${_target})
                target_compile_options(${_target} PRIVATE -Wno-error)
            endif()
        endforeach()
    endif()

    file(GLOB TEST_SOURCES tests/*.cpp)

    add_executable(check
        ${TEST_SOURCES}
    )

    target_link_libraries(check
        formatter
        formatter_ex
        solver
        gtest_main
    )

    add_test(NAME check COMMAND check)
endif()
