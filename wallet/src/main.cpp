#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "../include/wallet.h"
#include "../../blockchain/src/hash.h"

using namespace std;

int main() {

    std::array<unsigned char, 32> seed = {0};


    randombytes_buf(seed.data(), seed.size());

    Wallet wallet(seed);

    std::cout << "Private Key: " << dataToHexString(wallet.getPrivateKey()) << std::endl;
    std::cout << "Public Key: " << dataToHexString(wallet.getPublicKey()) << std::endl;
    std::cout << "Address: " << dataToHexString(wallet.getAddr()) << std::endl;
    
    return 0;
}