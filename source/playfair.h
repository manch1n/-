#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include "common.h"
#include <unordered_map>
#include <utility>
namespace info_secu
{

class PlayFair : public Algobase
{
public:
    explicit PlayFair(std::string key = "manch1nchen");

    void encrypt(std::vector<DTYPE> &plain);
    void decrypt(std::vector<DTYPE> &cipher);

private:
    std::string _key;
    std::vector<std::vector<DTYPE>> _matrix;               //16*16 char matrix
    std::unordered_map<DTYPE, std::pair<int, int>> _index; //first is row index.second is column index
    static const size_t _rank = 16;

    void computeBase(std::vector<DTYPE> &plain, int dir);

    inline int CYCLE(int shift, int direction)
    {
        return (shift + direction) % _rank;
    }
};

} // namespace info_secu

#endif // !playfair_h