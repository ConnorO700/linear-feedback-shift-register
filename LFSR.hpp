#pragma once
#include <string>

class LFSR {
public:
	LFSR(std::string seed, int tap) : cSeed(seed), tap(tap) { len = seed.length(); }
	int step();
	int generate(int k);
	friend std::ostream& operator<<(std::ostream& out, const LFSR& right);
	int getLen() { return len; };
	void testPrint();
private:

	std::string cSeed; //current seed
	int tap; //get extra bit from somewhere in seed
	int len; //seed length
	int bit;

};
