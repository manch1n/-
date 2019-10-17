#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <limits>
#include <string>
#include <functional>
#include <algorithm>
#include <random>
#include <type_traits>
using namespace std::placeholders;

class copyable
{
};

class uncopyable
{
private:
	uncopyable(const uncopyable &) = delete;
	void operator=(const uncopyable &) = delete;
};

class Algobase
{
public:
	typedef unsigned char DTYPE;
	virtual std::vector<DTYPE> encrypt(std::function<void(std::vector<DTYPE> &)> f, std::vector<DTYPE> &plaintext);
	virtual std::vector<DTYPE> decrypt(std::function<void(std::vector<DTYPE> &)> f, std::vector<DTYPE> &cipertext);

	virtual void encrypt(std::vector<DTYPE> &plain) = 0;
	virtual void decrypt(std::vector<DTYPE> &cipher) = 0;

	static const DTYPE _ucharmax = std::numeric_limits<DTYPE>::max();
	static const DTYPE _ucharmin = std::numeric_limits<DTYPE>::min();
	static const int _ucharRange = _ucharmax - _ucharmin + 1;
};

//some compact matrix function
inline int dotmul(const std::vector<int> &vec, const std::vector<int> &col)
{
	int sum = 0;
	for (int i = 0; i < vec.size(); ++i)
	{
		sum += vec[i] * col[i];
	}
	return sum;
}

template <typename T=Algobase::DTYPE>
std::vector<T> createRandom(size_t size)
{
	if (size <= 0||std::is_arithmetic<T>::value==false)
	{
		return {};
	}
	std::random_device rd;
	std::uniform_int_distribution<int> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	std::vector<T> vec(size);
	for (int i = 0; i < size; ++i)
	{
		vec[i] = static_cast<T>(dist(rd));
	}
	return vec;
}

//Gauss-Jordan Elimination method to get inverse matrix
template <typename T = double>
std::vector<std::vector<double>> matrixInversion(const std::vector<std::vector<T>> &a)
{
	const static double eps = 1e-6;
	std::vector<std::vector<double>> augma; //augmented matrix
	for (auto &vec : a)
	{
		std::vector<double> tmp;
		std::transform(vec.begin(), vec.end(), std::back_inserter(tmp), [](const T interger) {
			return static_cast<double>(interger);
		});
		augma.push_back(std::move(tmp));
	}
	int rank = a.size();
	//init
	for (int i = 0; i < rank; ++i)
	{
		augma[i].resize(rank * 2);
		augma[i][rank + i] = 1;
	}
	for (int i = 0; i < rank; ++i)
	{
		if (::abs(augma[i][i]) < eps)
		{
			int j;
			for (j = i + 1; j < rank; ++j)
			{
				if (::abs(augma[j][i]) > eps)
					break;
			}
			if (j == rank)
				return {};
			for (int r = i; r < 2 * rank; ++r)
			{
				augma[i][r] += augma[j][r];
			}
		}
		double ep = augma[i][i];
		for (int r = i; r < 2 * rank; ++r)
		{
			augma[i][r] /= ep;
		}

		for (int j = i + 1; j < rank; ++j)
		{
			double e = -1 * (augma[j][i] / augma[i][i]);
			for (int r = i; r < 2 * rank; ++r)
			{
				augma[j][r] += e * augma[i][r];
			}
		}
	}
	for (int i = rank - 1; i >= 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			double e = -1 * (augma[j][i] / augma[i][i]);
			for (int r = i; r < 2 * rank; ++r)
			{
				augma[j][r] += e * augma[i][r];
			}
		}
	}

	for (auto &vec : augma)
	{
		vec.erase(vec.begin(), vec.begin() + rank);
	}

	return augma;
}

#endif