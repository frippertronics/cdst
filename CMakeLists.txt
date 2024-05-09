cmake_minimum_required(VERSION 3.24)

set(C_STANDARD 99)
project(
    cstd 
    VERSION 1.0
    LANGUAGES C
)

set(PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_BINARY_DIR build)
set(CMAKE_BUILD_TYPE Release)

option(BUILD_UNITTEST "Compile unit tests" OFF)
option(DISABLE_EUROPE_RULES "Disable European countries" OFF)
option(DISABLE_AMERICA_RULES "Disable American countries" OFF)
option(DISABLE_AFRICA_RULES "Disable African countries" OFF)
option(DISABLE_ASIA_RULES "Disable Asian countries" OFF)
option(DISABLE_OCEANIA_RULES "Disable Oceanian countries" OFF)

# Compile CDST library
add_library(${PROJECT_NAME} STATIC src/cdst.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Werror
    -ffunction-sections -fdata-sections -fno-strict-aliasing
    "$<$<CONFIG:Debug>:-O0;-g>"
    "$<$<CONFIG:Release>:-O2>"
)
target_compile_definitions(${PROJECT_NAME} PUBLIC
    "$<$<BOOL:${DISABLE_EUROPE_RULES}>:-DDISABLE_EUROPE_RULES>"
    "$<$<BOOL:${DISABLE_AMERICA_RULES}>:-DDISABLE_AMERICA_RULES>"
    "$<$<BOOL:${DISABLE_AFRICA_RULES}>:-DDISABLE_AFRICA_RULES>"
    "$<$<BOOL:${DISABLE_ASIA_RULES}>:-DDISABLE_ASIA_RULES>"
    "$<$<BOOL:${DISABLE_OCEANIA_RULES}>:-DDISABLE_OCEANIA_RULES>"
)

# Compile tests
if(${BUILD_UNITTEST})
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
