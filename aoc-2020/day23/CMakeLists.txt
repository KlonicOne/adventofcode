cmake_minimum_required(VERSION 3.0.0)
project(day23 VERSION 0.1.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(PRJ_SRC
    main.cpp 
    load_data.cpp
    day23.cpp
)

add_executable(${PROJECT_NAME} ${PRJ_SRC})
