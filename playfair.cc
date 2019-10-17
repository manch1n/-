#include "playfair.h"

namespace info_secu
{

PlayFair::PlayFair(std::string key) : _key(key) //for brevity and confidentially key size should be 16 or larger
{
    std::vector<DTYPE> all;
    bool used[_ucharRange]{false};
    //input the key
    for (auto c : key)
    {
        if (used[static_cast<int>(c)] == false)
        {
            used[static_cast<int>(c)] = true;
            all.push_back(c);
        }
    }
    //fill the left
    for (int i = _ucharmin; i <= _ucharmax; ++i)
    {
        if (!used[i])
        {
            all.push_back(static_cast<DTYPE>(i));
        }
    }
    //turn 1d to 2dimension
    for (int i = 0; i < _rank; i++)
    {
        std::vector<DTYPE> tmp;
        for (int j = 0; j < _rank; ++j)
        {
            tmp.push_back(all[i * _rank + j]);
            _index[all[i * _rank + j]] = std::make_pair(i, j);
        }
        _matrix.push_back(tmp);
    }
}

void PlayFair::computeBase(std::vector<DTYPE> &plain, int dir)
{
    std::vector<DTYPE> tmp;
    for (int i = 0;;)
    {
        if (i >= plain.size())
        {
            break;
        }
        if (i == plain.size() - 1)
        {
            //for simplicity,directly push
            tmp.push_back(plain[i]);
            i += 1;
            break;
        }
        char a = plain[i], b = plain[i + 1];
        if (a != b)
        {
			auto [ia0, ia1] = _index[a];
			auto [ib0,ib1] = _index[b];
            if (ia0 == ib0) //in the same row
            {
                char c1 = _matrix[ia0][CYCLE(ia1, dir)];
                char c2 = _matrix[ib0][CYCLE(ib1, dir)];
                tmp.push_back(c1);
                tmp.push_back(c2);
            }
            else if (ia1 == ib1) //in the same column
            {
                char c1 = _matrix[CYCLE(ia0, dir)][ia1];
                char c2 = _matrix[CYCLE(ib0, dir)][ib1];
				tmp.push_back(c1);
				tmp.push_back(c2);
            }
            else //not in the same row and column
            {
                tmp.push_back(_matrix[ia0][ib1]);
                tmp.push_back(_matrix[ib0][ia1]);
            }
            i += 2;
        }
        else
        {
            //for simplicity,directly push
            tmp.push_back(a);
            tmp.push_back(b);
            i += 2;
        }
    }
    std::swap(plain, tmp);
}

void PlayFair::encrypt(std::vector<DTYPE> &plain)
{
    computeBase(plain, 1);
}

void PlayFair::decrypt(std::vector<DTYPE> &cipher)
{
    computeBase(cipher, -1);
}

} // namespace info_secu