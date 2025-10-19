cmake_minimum_required(VERSION 4.1.2)
project(RegexEngine VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a library from src files
add_library(RegexE
    src/lexer.cpp
    src/parser.cpp
    src/ast.cpp
    src/nfa.cpp
)

# Include directories for the library
target_include_directories(RegexE
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: add an executable for testing
add_executable(regex test/main.cpp)

# Link library to the executable
target_link_libraries(regex PRIVATE RegexE)
