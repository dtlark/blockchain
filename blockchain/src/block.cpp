#include "block.h"
#include <algorithm>

std::array<unsigned char, 32> BlockHeader::hash() {
    return doubleSha256(serialize(const_cast<const BlockHeader&>(*this)));
}

std::array<unsigned char, 32> BlockHeader::getMerkleRoot(const std::vector<std::array<unsigned char, 32>>& txIDs) {
    if (txIDs.empty())
        return {};

    std::vector<std::array<unsigned char, 32>> merkleTree = txIDs;

    while (merkleTree.size() > 1) {
        if (merkleTree.size() % 2 != 0)
            merkleTree.push_back(merkleTree.back());

        std::vector<std::array<unsigned char, 32>> temp;

        for (size_t i = 0; i < merkleTree.size(); i += 2) {
            std::array<unsigned char, 64> concatenated;
            std::copy(merkleTree[i].begin(), merkleTree[i].end(), concatenated.begin());
            std::copy(merkleTree[i + 1].begin(), merkleTree[i + 1].end(), concatenated.begin() + 32);

            temp.push_back(doubleSha256(concatenated));
        }
        merkleTree = temp;
    }
    return merkleTree[0];
}

std::vector<std::array<unsigned char, 32>> BlockHeader::getMerklePath(const std::vector<std::array<unsigned char, 32>>& txIDs, const std::array<unsigned char, 32>& targetTxID) {
    std::vector<std::array<unsigned char, 32>> merklePath;
    
    if (txIDs.empty())
        return merklePath;

    int idx = 0;
    for(; idx < txIDs.size(); ++idx)
        if(txIDs[idx] == targetTxID)
            break;

    if (idx >= txIDs.size())
        return merklePath;

    std::vector<std::array<unsigned char, 32>> merkleTree = txIDs;
    size_t levelSize = txIDs.size();

    while (levelSize > 1) {
        size_t siblingIndex = (idx % 2 == 0) ? idx + 1 : idx - 1;
        if (siblingIndex < levelSize)
            merklePath.push_back(merkleTree[siblingIndex]);
        else
            merklePath.push_back({});

        idx /= 2;
        levelSize = (levelSize + 1) / 2;
    }

    return merklePath;
}

BlockHeader Block::getBlockHeader() const {
    return blockHeader_;
}
