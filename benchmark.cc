//discription:test serveral algorithm capability in 1,000 to 10,000,000 bytes
#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>

#include "ceasar.h"
#include "hill.h"
#include "playfair.h"
#include "common.h"

using namespace std;
using namespace std::chrono;
using namespace info_secu;
void testbase(Algobase& a) 
{
	for (int i = 10000; i <= 10000000; i *= 10)
	{
		auto testdata = ::createRandom(i);
		vector<Algobase::DTYPE> vec(testdata); //in case that the default constructor to initial to zero 
		auto start = system_clock::now();   //test encrypt
		a.encrypt(vec);
		auto end = system_clock::now();
		auto du = duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "encrypt "<<setw(10)<<i<<" bytes:" << setw(12) << right<< du.count() << "us   ";
		start = system_clock::now();
		a.decrypt(vec);									//test decrypt
		end = system_clock::now();
		du = duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "decrypt " << setw(10) << i << " bytes:" << setw(12) << right << du.count() << "us   ";
		bool pass = true;
		for (int j = 0; j < i; ++j)
		{
			if (vec[j] != testdata[j])
			{
				std::cout << "test false" << std::endl;
				pass = false;
				break;
			}
		}
		if (pass)
		{
			std::cout << "test success!" << std::endl;
		}
	}
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
}

int main(int argc, char** argv)
{
	Ceaser c;
	std::cout << "Ceaser" << std::endl;
	testbase(c);
	PlayFair p;
	std::cout << "PlayFair" << std::endl;
	testbase(p);
	Hill h;
	std::cout << "Hill" << std::endl;
	testbase(h);
	std::getchar();
	return 0;
}