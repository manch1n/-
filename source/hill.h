/*
** EPITECH PROJECT, 2019
** hill
** File description:
** information security homework
*/

#ifndef HILL_H_
#define HILL_H_
#include <random>
#include "common.h"
namespace info_secu
{

class Hill : public Algobase          
{
public:                                    
    explicit Hill(int rank = 4, int rmin = 1, int rmax = 10); //the range should exclude zero so that could get the inverse matrix by GJ elimination method
    void encrypt(std::vector<DTYPE> &plain);
    void decrypt(std::vector<DTYPE> &cipher);

private:
    void computeBase(std::vector<DTYPE> &text, const std::vector<std::vector<int>> &matrix);

    std::vector<std::vector<int>> _keyMatrix;
    std::vector<std::vector<int>> _inverseMatrix;
    int _maRank;
    int _rmin;
    int _rmax;
};

} // namespace info_secu

#endif /* !HILL_H_ */
