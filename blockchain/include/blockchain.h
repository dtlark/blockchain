#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <array>
#include <leveldb/db.h>
#include "block.h"

class Blockchain {
    leveldb::DB* blockDB_;
    uint64_t height_;
    uint8_t difficulty_;

public:
    Blockchain(const std::string& dbPath = "./block_db");
    ~Blockchain();
    void addBlock(const Block& block);
};
