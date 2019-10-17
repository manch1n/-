#include "common.h"

std::vector<Algobase::DTYPE> Algobase::encrypt(std::function<void(std::vector<DTYPE> &)> f, std::vector<DTYPE> &plaintext)
{
    std::vector<DTYPE> cipher(plaintext);
    f(cipher);
    return cipher;
}

std::vector<Algobase::DTYPE> Algobase::decrypt(std::function<void(std::vector<DTYPE> &)> f, std::vector<DTYPE> &cipertext)
{
    std::vector<DTYPE> plain(cipertext);
    f(plain);
    return plain;
}
