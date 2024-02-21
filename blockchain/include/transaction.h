#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "hash.h"
#include <sodium.h>

using namespace std;

class TxInput {
public:
    std::array<unsigned char, 32> prevTXOHash_;
    uint32_t prevOIdx_;
    std::array<unsigned char, 32> publicKey_;
    std::array<unsigned char, 32> signature_;
};

class TxOutput {
public:
    uint64_t value_;
    std::array<unsigned char, 32> toAddr_;
};

class TxData {
public:
    vector<TxInput> inputs_;
    vector<TxOutput> outputs_;

    TxData(vector<TxInput> inputs, vector<TxOutput> outputs)  : inputs_(inputs), outputs_(outputs) {}
};

class Transaction {
public:
    std::array<unsigned char, 32> txID_;
    uint32_t version_ = 0;
    const TxData txData;

public:

    Transaction() = delete;
    Transaction(vector<TxInput> inputs, vector<TxOutput> outputs) : txData(TxData(inputs, outputs)) {
        txID_ = doubleSha256(serialize(txData));
    }
};
