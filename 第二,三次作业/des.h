#ifndef DES_H
#define DES_H

#include "common.h"
#include <bitset>

namespace info_secu
{

#define PERMUTE(act, pas, table, count, shift)  \
	do                                          \
	{                                           \
		for (int i = 0; i < (count); ++i)       \
		{                                       \
			act[i] = pas[(table[i]) + (shift)]; \
		}                                       \
	} while (0)

class Des : public Algobase
{
public:
	using Algobase::DTYPE;
	typedef uint64_t TYPE64;
	typedef uint32_t TYPE32;
	typedef std::bitset<64> BITS64;
	typedef std::bitset<48> BITS48;
	typedef std::bitset<32> BITS32;
	typedef std::bitset<56> BITS56;
	const int SIZE64 = 8;
	const int SIZE32 = 4;
	const int SIZE48 = 6;
	const int SIZE56 = 7;

public:
	explicit Des(BITS64 bs = BITS64(0x0808));
	//private:
	void encrypt(std::vector<DTYPE> &plain);
	void decrypt(std::vector<DTYPE> &cipher);

	template <typename T>
	inline TYPE64* CAST64P(T e)
	{
		if (std::is_pointer<T>::value == false)
		{
			return nullptr;
		}
		return reinterpret_cast<TYPE64*>(e);
	}

private:
	void keyPermute(BITS64 &key);

	void initShiftKeys(); //should be call afer keypermute
	std::function<void(BITS64&)> initPermute = std::bind(&Des::initPermuteBase,*this, std::placeholders::_1, _ipTable);
	std::function<void(BITS64&)> invePermute = std::bind(&Des::initPermuteBase, *this, std::placeholders::_1, _ipInTable);
	void initPermuteBase(BITS64 &data, const size_t table[64]);

	inline void CYCLESHIFT(std::string &bs)
	{
		auto c = bs[0];
		bs.erase(bs.begin());
		bs.push_back(c);
	}

	BITS48 exPermute(const BITS32 &data);
	BITS32 subBox(const BITS48 &data);
	void permuteBox(BITS32 &data);
	void renewed(BITS32 &left, BITS32 &right, int round);

private:
	BITS56 _key;
	std::vector<BITS48> _shiftKeys;
	//permute tables
	const static size_t _ipTable[64];
	const static size_t _ipInTable[64];
	const static size_t _keyTable[56];
	const static size_t _shiftTable[16];
	const static size_t _keyCompressTable[48];
	const static size_t _extendTable[48];
	const static size_t _permuteBox[32];
	std::vector<std::vector<size_t>> _SBox;
};

inline Des::BITS48 Des::exPermute(const Des::BITS32 &data)
{
	BITS48 extend;
	PERMUTE(extend, data, _extendTable, 48, -1);
	return extend;
}

inline Des::BITS32 Des::subBox(const BITS48 &data)
{
	BITS32 result;
	for (int i = 0; i < 8; ++i)
	{
		int row = data[i * 6] + data[i * 6 + 5] * 2; //very slow
		int column = data[i * 6 + 1] + data[i * 6 + 2] * 2 + data[i * 6 + 3] * 4 + data[i * 6 + 4] * 8;
		BITS32 tmp(_SBox[i][row * 16 + column]);
		for (int j = 0; j < 4; ++j)
		{
			result[j + i * 4] = tmp[j];
		}
	}
	return result;
}

inline void info_secu::Des::permuteBox(BITS32 &data)
{
	BITS32 tmp(data);
	PERMUTE(data, tmp, _permuteBox, 32, -1);
}

inline void Des::renewed(BITS32 &left, BITS32 &right, int round)
{
	//BITS32 rtmp(right);
	BITS48 rextent = exPermute(right);
	rextent ^= _shiftKeys[round];
	BITS32 rsubbox = subBox(rextent);
	permuteBox(rsubbox);
	left ^= rsubbox;
	//right =left^ rsubbox;
	//left = rtmp;
}

//inline void Des::initPermute(BITS64 &data)
//{
//	initPermuteBase(data, _ipTable);
//}

inline void Des::initPermuteBase(BITS64 &data, const size_t table[64])
{
	BITS64 tmp(data);
	PERMUTE(data, tmp, table, 64, -1);
}

} // namespace info_secu

#endif //!DES_H