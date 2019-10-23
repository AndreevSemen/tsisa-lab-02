cmake_minimum_required(VERSION 3.4)

project(search)

add_library(random-search STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/random_search.cpp
        )
target_include_directories(random-search
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
        )
target_include_directories(main
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(main random-search)
