cmake_minimum_required(VERSION 3.24)

set(C_STANDARD 99)
project(
    cstd 
    VERSION 1.0
    LANGUAGES C
)

set(PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_BINARY_DIR build)
option(BUILD_UNITTEST "Compile unit tests" ON)

# Compile CDST library
add_library(${PROJECT_NAME} STATIC src/cdst.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_options(${PROJECT_NAME} PRIVATE
    -O0 -g
    -Wall -Werror
    -ffunction-sections -fdata-sections -fno-strict-aliasing
    "$<$<CONFIG:Debug>:-O0;-g>"
    "$<$<CONFIG:Release>:-O2>"
)

if(${BUILD_UNITTEST})
    # Compile tests
    include(CTest)
    add_subdirectory(extern)

    add_executable(test_cstd
        tests/test_cdst.c
    )
    target_include_directories(test_cstd PRIVATE
        src
    )
    target_compile_options(test_cstd PRIVATE
        -O0 -g
        -Wall -Werror
        -ffunction-sections -fdata-sections -fno-strict-aliasing
    )
    target_link_libraries(test_cstd
        ${PROJECT_NAME}
        unity
    )

    add_test(test_suite test_cstd)
endif()
