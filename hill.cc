#include "hill.h"
namespace info_secu
{

Hill::Hill(int rank, int rmin, int rmax) : _maRank(rank), _rmin(rmin), _rmax(rmax)
{
	//   //construct the key matrix
	//   std::random_device rd;
	//   std::uniform_int_distribution<int> dist(rmin, rmax);
	//   for (int i = 0; i < _maRank; ++i)
	//   {
	//       std::vector<int> tmp;
	//       for (int j = 0; j < _maRank; ++j)
	//       {
	//           tmp.push_back(dist(rd));
	//       }
	//	tmp.resize(_maRank);
	//       _keyMatrix.push_back(tmp);
	//   }
	//_keyMatrix.resize(_maRank);
	//   //cauculate the inverse matrix
	//auto dtmp = ::matrixInversion(_keyMatrix);
	//for (auto& vec : dtmp)
	//{
	//	std::vector<int> itmp;
	//	std::transform(vec.begin(), vec.end(), std::back_inserter(itmp), [](double ddata)
	//		{
	//			return static_cast<int>(ddata);
	//		});
	//	_inverseMatrix.push_back(std::move(itmp));
	//}
	_keyMatrix.push_back({8, 6, 9, 5});
	_keyMatrix.push_back({6, 9, 5, 10});
	_keyMatrix.push_back({5, 8, 4, 9});
	_keyMatrix.push_back({10, 6, 11, 4});

	_inverseMatrix.push_back({253, 20, 235, 1});
	_inverseMatrix.push_back({2, 215, 44, 1});
	_inverseMatrix.push_back({2, 250, 6, 255});
	_inverseMatrix.push_back({255, 28, 226, 255});
}

void Hill::encrypt(std::vector<DTYPE> &plain)
{
	computeBase(plain, _keyMatrix);
}

void Hill::decrypt(std::vector<DTYPE> &cipher)
{
	computeBase(cipher, _inverseMatrix);
}

void Hill::computeBase(std::vector<DTYPE> &text, const std::vector<std::vector<int>> &matrix)
{
	std::vector<DTYPE> cipher;
	for (int i = 0;;)
	{
		if (i > text.size() - _maRank)
		{
			for (int j = i; j < text.size(); ++j) //for brivity push the left
			{
				cipher.push_back(text[j]);
			}
			break;
		}
		auto iter = matrix.cbegin();
		std::vector<int> tmp;
		std::transform(text.begin() + i, text.begin() + i + _maRank, std::back_inserter(tmp), [](DTYPE ucdata) {
			return static_cast<int>(ucdata);
		});
		for (int j = 0; j < _maRank; ++j)
		{
			int dot = ::dotmul(tmp, *(iter + j));
			cipher.push_back(static_cast<DTYPE>(dot % _ucharRange));
		}
		i += _maRank;
	}
	std::swap(cipher, text);
}

} // namespace info_secu