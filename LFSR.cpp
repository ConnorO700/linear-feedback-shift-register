#include <iostream>
#include <string>
#include <math.h>
//#include <Windows.h>
#include "LFSR.hpp"
using namespace std;







int LFSR::step() {
	char hold = cSeed.at(0);
	char taph = cSeed.at(len-tap-1);
	string newSeed = "";
	
	if (((hold =='0' )&& (taph == '0')) ||((hold == '1') &&( taph == '1'))) {//Xor operation if both hold & tap are 0 or 1
		//cout << "  IF XOR: " << hold << " & " << taph << " == 0" << endl;
		bit = 0;
	}
	else {					//otherwise it must be a 1
		//cout << "ELSE XOR: " << hold << " & " << taph << " == 1" << endl;
		bit = 1; 
	}
	for (int i = 0; i <= len - 2; i++) {
		cSeed.at(i) = cSeed.at(i + 1);
	}
	cSeed.at(len - 1) = bit + 48; //puts bit into least sig digit. 
	return bit; 
}

int LFSR::generate(int k) {
	int re = 0; 
	for (int i = 0; i < k; i++) {
		int t = step(); 
		if (t == 1) {
			re += pow(2, k-i-1); 
		}
	}
	return re; 
}
ostream& operator<<(ostream& out, const LFSR& right) {
	out << right.cSeed;
	return out;
}
/*
void LFSR::testPrint() {
	for (int i = 0; i < len; i++) {
		if (i == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << cSeed.at(i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (i == len-tap-1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << cSeed.at(i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else {
			cout << cSeed.at(i);
		}
	}

}
*/
