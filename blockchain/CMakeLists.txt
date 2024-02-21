cmake_minimum_required(VERSION 3.10)
project(blockchain)

option(DEBUG "Enable debugging" ON)

set(CMAKE_CXX_STANDARD 11)

include_directories("./include/")
file(GLOB_RECURSE SOURCES "src/*.cpp")

set(SODIUM_INCLUDE_DIR "/usr/include/sodium")
set(SODIUM_LIBRARY "/usr/lib/x86_64-linux-gnu/libsodium.so")

set(LEVELDB_INCLUDE_DIR "/usr/include/leveldb")
set(LEVELDB_LIBRARY "/usr/lib/x86_64-linux-gnu/libleveldb.so")

add_executable(blockchain main.cpp ${SOURCES})

target_include_directories(blockchain PRIVATE ${SODIUM_INCLUDE_DIR} ${LEVELDB_INCLUDE_DIR})
target_link_libraries(blockchain PRIVATE ${SODIUM_LIBRARY} ${LEVELDB_LIBRARY})
