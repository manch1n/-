#ifndef CEASER_H
#define CEASER_H

#include "common.h"
namespace info_secu
{

class Ceaser : public Algobase
{
public:
    explicit Ceaser(DTYPE offset=3);        //默认偏移量为3
    void encrypt(std::vector<DTYPE> &plain);
    void decrypt(std::vector<DTYPE> &cipher);

private:
    DTYPE _offset;
};

} // namespace info_secu

#endif // !CEASER_H