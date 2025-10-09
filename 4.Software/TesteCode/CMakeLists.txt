cmake_minimum_required(VERSION 3.15)
project(TesteCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add sources
add_executable(TesteCode
    main.cpp
    RingBuffer.cpp
)

# Use project directory for includes
target_include_directories(TesteCode PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Optional: enable warnings
if (MSVC)
    target_compile_options(TesteCode PRIVATE /W4)
else()
    target_compile_options(TesteCode PRIVATE -Wall -Wextra -Wpedantic)
endif()