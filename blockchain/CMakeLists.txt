cmake_minimum_required(VERSION 3.10)
project(blockchain)

option(DEBUG "Enable debugging" ON)

set(CMAKE_CXX_STANDARD 11)

set(SODIUM_INCLUDE_DIR "/usr/include/sodium")
set(SODIUM_LIBRARY_RELEASE "/usr/lib/x86_64-linux-gnu/libsodium.so")

add_executable(blockchain main.cpp)

target_include_directories(blockchain PRIVATE ${SODIUM_INCLUDE_DIR})
target_link_libraries(blockchain PRIVATE ${SODIUM_LIBRARY_RELEASE})
