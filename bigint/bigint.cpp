
/**
* Jeremiah Heck
* bigint
* CS 23001
*/

#include "bigint.hpp"
#include <iostream>
#include <fstream>
//#include <cstdlib>

bigint::bigint() {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}
}

bigint::bigint(int x) {
	//make sure array is initialized too zero once more
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}
	//begin determining the size of the number right to left, ones at 0, tens at 1 etc...
	int countSize = 0;
	while (x > 0) {
		number[countSize] = x % 10;
		x = x / 10;
		countSize++;
	}
}

bigint::bigint(const char x[]) {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}

	//find size
	int size = 0;

	while (x[size] != '\0') {
		++size;
	}

	int bSize = size - 1;
	//find actual numbers?
	for (int i = 0; size > i; ++i) {
		if (x[i] >= 0) {
			char f = x[i];
			int g = f - '0';
			number[bSize] = g;
			bSize--;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const bigint& b) {
	int iterate = 0;
	bool first = false;
	for (int i = CAPACITY; i >= 0; --i) {
		if (b.number[i] > 0 || first == true) {
			os << b.number[i];
			iterate++;
			first = true;
			if (iterate == 80) {
				os << std::endl;
				iterate = 0;
			}
		}
	}
	return os;
}

bool bigint::operator==(int v) {
	bigint b(v);
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != b.number[i]) {
			return false;
		}
	} return true;
}
bool bigint::operator==(bigint &x) {
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != x.number[i]) {
			return false;
		}
	} return true;
}


bool bigint::operator==(const char x[]) {
	bigint b(x);
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != b.number[i]) {
			return false;
		}
	} return true;
}

bigint bigint::operator+(bigint& x) {
	bigint sum;

	//for some reason aa few inexs are negative...?
	for (int i = 0; i < CAPACITY; i++) {
		if (number[i] < 0) {
			number[i] = 0;
		}
	}
	for (int i = 0; i < CAPACITY; i++) {
		if (x.number[i] < 0) {
			x.number[i] = 0;
		}
	}

	int ones = 0;
	int tens = 0;
	int temp = 0;
	for (int i = 0; i < CAPACITY; i++) {
		temp += number[i];
		temp += x.number[i];
		temp += sum.number[i];
		temp += tens;
		tens = 0;
		if (temp >= 10 && temp <= 20) { //tens
			int tempTemp = temp;
			tempTemp = tempTemp % 10;
			ones = tempTemp;
			tens = 1;
		} else if (temp <= 9 && temp >= 0) { //ones
			ones = temp;
			tens = 0;
		} else if (temp >= 20) { //twenties
			int tempTemp = temp;
			tempTemp = tempTemp % 10;
			ones = tempTemp;
			tens = 2;
		}
		sum.number[i] += ones;
		//sum.number[i + 1] += tens;
		ones = 0;
		//tens = 0;
		temp = 0;
	}
	return sum;
}

bigint::bigint(int x[]) {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = x[i];
	}
}

int bigint::operator[] (const int index) const {
	return number[index];
}


bigint bigint::operator=(char x[]) {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}
	int size = 0;
	while (x[size] != '\0') {
		++size;
	}

	int bSize = size - 1;
	//find actual numbers?
	for (int i = 0; size > i; ++i) {
		if (x[i] >= 0) {
			char f = x[i];
			int g = f - '0';
			number[bSize] = g;
			bSize--;
		}
	}
	return number;
}

bigint bigint::timesDigit(const int x) {
	bigint sum, temp;
	
	for (int i = 0; i < CAPACITY; ++i) {
		temp.number[i] = number[i];
	}

	for (int i = 0; i < x; ++i) {
		sum = sum + temp;
	}

	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = sum.number[i];
	}

	return number;
}

bigint bigint::timesTen(const int x) {
	bigint temp(0);

	for (int i = CAPACITY; i >= 0; --i) {
		if (number[i] > 0) {
			temp.number[i + x] = number[i];
		}
	}

	//initialize the new value to the bigint
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = temp.number[i];
	}

	return number;
}

bigint bigint::operator*(bigint& B) {

	//To compute A * B
	//B[0] is 1s place, B[1] is 10s place, B[2] is 100s place, etc.
	bigint temp;
	bigint product(0);
	for (int i = 0;i < CAPACITY;++i){
		//product = product + ( (A * B[i]) * 10^i )
		if (B[i] > 0) {
			temp = timesDigit(B[i]);
		}
		product = product + temp.timesTen(i);
		std::cout << product << "|";
	}


	return product;
}