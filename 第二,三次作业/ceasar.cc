#include "ceasar.h"
namespace info_secu
{

Ceaser::Ceaser(DTYPE off) : _offset(off) {}

void Ceaser::encrypt(std::vector<DTYPE> &plain)
{
    for (auto &c : plain)
    {
        c = (c + _offset) % _ucharRange;
    }
}

void Ceaser::decrypt(std::vector<DTYPE> &cipher)
{
    for (auto &c : cipher)
    {
        c = (c - _offset) % _ucharRange;
    }
}

} // namespace info_secu