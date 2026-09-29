cmake_minimum_required(VERSION 3.25)
project(nyancat_network VERSION 0.1.0 LANGUAGES CXX)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    message(FATAL_ERROR "Use GCC 13 or newer. The provided Codespace has the right compiler.")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) # -std=gnu++23
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(nyan_core
    src/cli.cpp
    src/socket.cpp
    src/connect.cpp
    src/io.cpp
    src/terminal.cpp
    src/telnet/encode.cpp
    src/telnet/parser.cpp
    src/telnet/terminal_type.cpp
    src/telnet/window_size.cpp
    src/telnet/session.cpp
)
target_include_directories(nyan_core PUBLIC include)
target_compile_options(nyan_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(nyancat-client src/main.cpp)
target_link_libraries(nyancat-client PRIVATE nyan_core)
target_compile_options(nyancat-client PRIVATE -Wall -Wextra -Wpedantic)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
