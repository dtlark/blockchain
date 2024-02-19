cmake_minimum_required(VERSION 3.10)
project(wallet)

option(DEBUG "Enable debugging" ON)

set(CMAKE_CXX_STANDARD 11)

set(SODIUM_INCLUDE_DIR "/usr/include/sodium")
set(SODIUM_LIBRARY_RELEASE "/usr/lib/x86_64-linux-gnu/libsodium.so")

add_executable(wallet src/main.cpp)

target_include_directories(wallet PRIVATE ${SODIUM_INCLUDE_DIR})
target_link_libraries(wallet PRIVATE ${SODIUM_LIBRARY_RELEASE})
