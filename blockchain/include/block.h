#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include "transaction.h"

class BlockHeader {
    std::array<unsigned char, 32> prevBlockHash_;
    std::array<unsigned char, 32> merkleRoot_;
    uint32_t version_;
    uint32_t timestamp_;
    uint32_t difficulty_;
    uint32_t nonce_;

public:
    std::array<unsigned char, 32> hash();
    std::array<unsigned char, 32> getMerkleRoot(const std::vector<std::array<unsigned char, 32>>& txIDs);
    std::vector<std::array<unsigned char, 32>> getMerklePath(const std::vector<std::array<unsigned char, 32>>& txIDs, const std::array<unsigned char, 32>& targetTxID);
};

class Block {
    BlockHeader blockHeader_;
    uint32_t blockSize_;
    uint32_t txCount_;
    std::vector<Transaction> transactions_;

public:
    BlockHeader getBlockHeader() const;
};
