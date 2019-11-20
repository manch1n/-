#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>
#include "des.h"
using namespace std;
using namespace info_secu;
#pragma warning(disable:4996)


int main(int argc, char **argv)
{
	std::vector<unsigned char> vec;
	vec.reserve(sizeof(uint64_t));
	vec.resize(sizeof(uint64_t));
	uint64_t key = 1;
	double diffcount = 0;
	for (int i = 0; i < 32; ++i)
	{
		Des d(key);
		uint64_t data = 0x0808;
		*d.CAST64P(vec.data()) = data;
		bitset<64> before(data);
		d.encrypt(vec);
		bitset<64> after(*d.CAST64P(vec.data()));
		diffcount += (before ^ after).count();
	}
	diffcount /= 32;
	std::cout << diffcount << std::endl;
	std::getchar();
	return 0;
}
