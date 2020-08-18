/**
* Jeremiah Heck
* bigint
* CS 23001
*/

// Basics for openning a file for milestone 2 of Project 1.
//
#include <iostream>
#include <fstream>
//#include <cstdlib>
#include "bigint.hpp"

int main() {
	bigint b1;
	char d[CAPACITY] = { '0' };
	std::ifstream in("data1-1.txt");
	if (!in) {
		std::cerr << "cant" << std::endl;
		exit(1);
	}
	bigint left;
	bigint right;
	bigint sum;
	
	for (int x = 0; 3 > x; ++x) {
		char delimeter = ';';
		char singleCharacter;
		in.get(singleCharacter);
		char arrayC[CAPACITY] = { '0' };
		std::cout << arrayC[1];
		int i = 0;
		//for the left side
		while (singleCharacter != delimeter) {

			arrayC[i] = singleCharacter;
			in.get(singleCharacter);
			i++;
		}
		left = arrayC;
		std::cout << left << std::endl;
		//do it for the right side
		singleCharacter;
		in.get(singleCharacter);
		char arrayC1[CAPACITY] = { '0' };
		i = 0;
		while (singleCharacter != delimeter) {

			arrayC1[i] = singleCharacter;
			in.get(singleCharacter);
			i++;
		}
		right = arrayC1;
		std::cout << right << std::endl;
		sum = left + right;
		std::cout << '{' << sum << '}' << std::endl;
	}
	
	in.close();
	system("pause");
}
