#pragma once
#include <sodium.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <array>
#include <cstring>

template<size_t N>
std::array<unsigned char, 32> sha256(const std::array<unsigned char, N>& data) {
    std::array<unsigned char, 32> hash;
    crypto_hash_sha256(hash.data(), data.data(), data.size());
    return hash;
}

template<size_t N>
std::array<unsigned char, 32> doubleSha256(const std::array<unsigned char, N>& data) {
    std::array<unsigned char, 32> hash1 = sha256(data);
    return sha256(hash1);
}

template<typename T>
std::array<unsigned char, sizeof(T)> serialize(const T& obj) {
    std::array<unsigned char, sizeof(T)> result;
    const unsigned char* data = reinterpret_cast<const unsigned char*>(&obj);
    std::copy(data, data + sizeof(T), result.begin());
    return result;
}

template<size_t N>
std::string dataToHexString(const std::array<unsigned char, N>& data) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < data.size(); ++i) {
        ss << std::setw(2) << static_cast<int>(data[i]);
    }
    return ss.str();
}

static const char* base58Chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

std::string encodeBase58(const std::array<unsigned char, 32>& input) {
    std::string output;
    size_t zeros = 0;
    while (zeros < input.size() && input[zeros] == 0) {
        zeros++;
    }
    output.assign(zeros, '1');

    unsigned int carry;
    for (size_t i = zeros; i < input.size(); ++i) {
        carry = input[i];
        for (auto it = output.rbegin(); it != output.rend(); ++it) {
            carry += 256 * (*it - '1');
            *it = base58Chars[carry % 58];
            carry /= 58;
        }
        while (carry) {
            output.insert(output.begin(), base58Chars[carry % 58]);
            carry /= 58;
        }
    }

    return output;
}

std::array<unsigned char, 32> generateSeed(size_t sizeBytes = 32) {
    std::array<unsigned char, 32> seed;
    randombytes_buf(seed.data(), seed.size());
    return seed;
}
