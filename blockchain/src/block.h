#pragma once
#include <cstdint>
#include <vector>
#include <utility>
#include <iomanip>
#include <sodium.h>
#include "transaction.h"
#include "hash.h"

using namespace std;

class BlockHeader {
    std::array<unsigned char, 32> prevBlockHash_;
    std::array<unsigned char, 32> merkleRoot_;
    uint32_t version_;
    uint32_t timestamp_;
    uint32_t difficulty_;
    uint32_t nonce_;

public:

    std::array<unsigned char, 32> hash() { 
        return doubleSha256(serialize(const_cast<const BlockHeader&>(*this)));
    }
};

class Block {
    BlockHeader blockHeader;
    std::array<unsigned char, 32> blockHeaderHash_;
    uint32_t blockSize;
    uint32_t txCount;
    vector<Transaction> transactions;
};
