cmake_minimum_required(VERSION 3.10)

project(lab05hw)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)
option(COLLECT_COVERAGE "Collect coverage" OFF)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()

    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(third-party/gtest)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        foreach(_target gtest gtest_main gmock gmock_main)
            if(TARGET ${_target})
                target_compile_options(${_target} PRIVATE
                    -Wno-error
                    -Wno-maybe-uninitialized
                    -Wno-uninitialized
                )
            endif()
        endforeach()
    endif()

    add_subdirectory(tests)
endif()
