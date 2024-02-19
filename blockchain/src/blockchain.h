#pragma once
#include "block.h"

class Blockchain {
    std::vector<Block> blocks_;
    uint64_t height_;
    uint8_t difficulty_;
};