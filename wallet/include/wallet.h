#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <array>
#include <sodium.h>

class Wallet {
    std::array<unsigned char, crypto_sign_SECRETKEYBYTES> privateKey_;
    std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> publicKey_;
    std::array<unsigned char, crypto_generichash_BYTES> addr_;

public:
    Wallet() = delete;
    Wallet(const std::array<unsigned char, 32>& seed) {
        genKeypairs(seed);
        genAddr(publicKey_);
    }
    ~Wallet() = default;

    const std::array<unsigned char, crypto_sign_SECRETKEYBYTES>& getPrivateKey() const { return privateKey_; }
    const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& getPublicKey() const { return publicKey_; }
    const std::array<unsigned char, crypto_generichash_BYTES>& getAddr() const { return addr_; }

private:

    bool isValidKeypair(const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& publicKey, const std::array<unsigned char, crypto_sign_SECRETKEYBYTES>& privateKey) {
        unsigned char message[] = "Hello hello world";
        unsigned char signature[crypto_sign_BYTES];

        if (crypto_sign_detached(signature, NULL, message, sizeof(message), privateKey.data()) != 0)
            return false;

        if (crypto_sign_verify_detached(signature, message, sizeof(message), publicKey.data()) != 0)
            return false;

        return true;
    }

    void genKeypairs(const std::array<unsigned char, 32>& seed) {

        if (crypto_sign_ed25519_seed_keypair(publicKey_.data(), privateKey_.data(), seed.data()) != 0) {
            std::cout << "Keygen FAILED";
        }

        if (!isValidKeypair(publicKey_, privateKey_)) {
            std::cout << "Non Valid Pair!";
        } else {
            std::cout << "Keygen success";
        }
    }

    void genAddr(const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& publicKey) {
        std::array<unsigned char, crypto_generichash_BYTES> address;
        crypto_generichash(addr_.data(), sizeof(addr_), publicKey.data(), publicKey.size(), nullptr, 0);
    }
};
