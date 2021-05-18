cmake_minimum_required(VERSION 3.0.0)
project(day15 VERSION 0.1.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-std=gnu++17 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-std=gnu++17 -Wall -Wextra -Wpedantic")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: " ${ENABLE_UNIT_TESTS})

if (ENABLE_UNIT_TESTS)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/05CC6081FCBD0071053DE78238E136B3.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    enable_testing()

    add_executable(cpp_test "")
    target_sources(cpp_test
    PRIVATE
        test.cpp
    )

    target_link_libraries(cpp_test
    PRIVATE
        day15_func
        gtest_main
    )

endif()

set(PRJ_SRC
    main.cpp 
    load_data.cpp
)

add_library(day15_func
    STATIC
        day15.h
        show_container.h
        day15.cpp
)

add_executable(${PROJECT_NAME} ${PRJ_SRC})
target_link_libraries(${PROJECT_NAME} day15_func)
