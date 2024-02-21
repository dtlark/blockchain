#include "blockchain.h"

Blockchain::Blockchain(const std::string& dbPath) : height_(0), difficulty_(0) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, dbPath, &blockDB_);
    if (!status.ok()) {
        std::cerr << "Error opening database: " << status.ToString() << std::endl;
    }
}

Blockchain::~Blockchain() {
    delete blockDB_;
}

void Blockchain::addBlock(const Block& block) {
    std::array<unsigned char, 32> blockHeaderHash = sha256(block.getBlockHeader().hash());
    std::string strHash(blockHeaderHash.begin(), blockHeaderHash.end());

    auto serializedBlock = serialize(block);
    std::string strBlock(serializedBlock.begin(), serializedBlock.end());

    leveldb::Status status = blockDB_->Put(leveldb::WriteOptions(), strHash, strBlock);
    if (!status.ok()) {
        std::cerr << "Error adding block!: " << status.ToString() << std::endl;
        return;
    }
    ++height_;
}
