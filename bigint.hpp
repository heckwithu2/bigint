/**
* JEREMIAH HECK
* BIGINT
* CS 23001
*/

#ifndef BIGINT_HPP_
#define BIGINT_HPP_
#include <iostream>
#include <fstream>
//#include <cstdlib>


const int CAPACITY = 400;


class bigint {
private:
	//Tells how many digits there are that are not zero
	int size = 0;
	//determines the max capacity
	int number[CAPACITY];
public:
	//constructers
	bigint();
	bigint(int);
	bigint(long long);
	bigint(const char[]);
	bigint(int[]);

	//rule of five
	//ctor
	bigint(const bigint&);//copy ctor
	//bigint(bigint &&) noexcept = default;//move ctor
	bigint& operator=(const bigint&);//copy assignment
	//bigint& operator=(bigint &&) noexcept = default;//move assignment
	~bigint() noexcept = default;//dtor

	//methods/friends
	bigint timesDigit(const int);
	bigint timesTen(const int);
	void checkIfSizeisAccurate();
	//accessor at a specific index, the const at the end is for accessors
	int operator[] (const int) const;

	//operator overloading
	bigint operator-(long long&);
	bigint operator-(int&);
	bigint operator-(bigint&);
	bigint operator/(bigint&);
	bigint operator*(bigint);
	bigint operator+(int&);
	bigint operator+(bigint&);
	bigint operator=(char[]);
	bool operator>(bigint&);
	bool operator>=(bigint&);
	bool operator>=(long long&);
	bool operator>=(int&);
	bool operator==(const int);
	bool operator==(const bigint);
	bool operator==(const char x[]);

	//friends
	friend bigint factorial(bigint, bigint);
	friend std::ostream& operator<<(std::ostream& os, const bigint& bigint);
};

//Method Definitions
bigint::bigint() {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	} size = 0;
}

bigint::bigint(int numToBigint) {
	//make sure array is initialized to zero once more
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}
	//begin determining the size of the number right to left, ones at 0, tens at 1 etc...
	int countSize = 0;
	while (numToBigint > 0) {
		number[countSize] = numToBigint % 10;
		numToBigint = numToBigint / 10;
		countSize++;
	} size = countSize;
	this->checkIfSizeisAccurate();
}

bigint::bigint(long long numToBigint) {
	//make sure array is initialized too zero once more
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}
	//begin determining the size of the number right to left, ones at 0, tens at 1 etc...
	int countSize = 0;
	while (numToBigint > 0) {
		number[countSize] = numToBigint % 10;
		numToBigint = numToBigint / 10;
		countSize++;
	} size = countSize;
	this->checkIfSizeisAccurate();
}

bigint::bigint(int x[]) {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = x[i];
	}
	this->checkIfSizeisAccurate();
}

bigint::bigint(const char charArrayToBigint[]) {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = 0;
	}

	//find size
	size = 0;

	while (charArrayToBigint[size] != '\0') {
		++size;
	}

	int bSize = size - 1;
	int finalSize = 0;
	//find actual numbers
	for (int i = 0; size > i; ++i) {
		if (charArrayToBigint[i] >= 0) {
			char f = charArrayToBigint[i];
			int g = f - '0';
			number[bSize] = g;
			finalSize++;
			bSize--;
		}
	} size = finalSize;
	this->checkIfSizeisAccurate();
}

bigint::bigint(const bigint& copy) {
	this = copy;
}

bigint& bigint::operator=(const bigint& assignBigint) {
	if (this != &assignBigint) {
		//size
		for (int i = 0; i < CAPACITY; ++i) {
			number[i] = assignBigint.number[i];
		}
		this->checkIfSizeisAccurate();
		return *this;
	}	
}

void bigint::checkIfSizeisAccurate() {
	//make sure size is correct!
	//loop that counts backwards until a non zero is found
	for (int i = CAPACITY-1; i >= 0; --i) {
		if (number[i] > 0) {
			size = i + 1;
			break;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const bigint& outputThisBigint) {
	for (int i = outputThisBigint.size - 1;i >= 0; --i) {
		int iterate = 0;
		os << outputThisBigint.number[i];
		iterate++;
		if (iterate == 80) {
			os << std::endl;
			iterate = 0;
		}
	}
		return os;
}

bool bigint::operator==(const int checkAgainstInt) {
	bigint b(checkAgainstInt);
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != b.number[i]) {
			return false;
		}
	} return true;
}

bool bigint::operator==(const bigint checkAgainstBigint) {
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != checkAgainstBigint.number[i]) {
			return false;
		}
	} return true;
}


bool bigint::operator==(const char checkAgainstCharArray[]) {
	bigint b(checkAgainstCharArray);
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != b.number[i]) {
			return false;
		}
	} return true;
}

bool bigint::operator>=(bigint& checkAgainstBigint) {
	this->checkIfSizeisAccurate();
	checkAgainstBigint.checkIfSizeisAccurate();
	//if left is bigger than right
	if (size > checkAgainstBigint.size) {
		return true;
	}
	else if (size < checkAgainstBigint.size) {
		return false;
	}
	if (size == checkAgainstBigint.size) {
		for (int i = size; i >= 0; --i) {
			//if same size and number
			if (*this == checkAgainstBigint) {
				//if same size but not same number
				if (number[size] > checkAgainstBigint.number[size]) {
					return true;
				}
				else if (number[size] < checkAgainstBigint.number[size]) {
					return false;
				}
			} else {
				//they are the same number
				return true;
			}
		}
	}
	return false;
}

bool bigint::operator>=(int& checkAgainstInt) {
	bigint checkAgainstBigint(checkAgainstInt);
	if (*this >= checkAgainstInt) {
		return true;
	} else {
		return false;
	}
}

bool bigint::operator>=(long long& checkAgainstLongLong) {
	bigint checkAgainstBigint(checkAgainstLongLong);
	if (*this >= checkAgainstLongLong) {
		return true;
	} else {
		return false;
	}
}

bool bigint::operator>(bigint& checkAgainstBigint) {
	this->checkIfSizeisAccurate();
	checkAgainstBigint.checkIfSizeisAccurate();
	//if left is bigger than right
	if (size > checkAgainstBigint.size) {
		return true;
	}
	else if (size < checkAgainstBigint.size) {
		return false;
	}
	if (size == checkAgainstBigint.size) {
		for (int i = size; i >= 0; --i) {
			//if same size and number
			if (*this == checkAgainstBigint) {
				//if same size but not same number
				if (number[size] > checkAgainstBigint.number[size]) {
					return true;
				}
				else if (number[size] < checkAgainstBigint.number[size]) {
					return false;
				}
			} else {
				//they are the same number
				return false;
			}
		}
	}
	return false;
}

bigint bigint::operator+(bigint& addBigint) {
	bigint sum;

	int ones = 0;
	int tens = 0;
	int temp = 0;
	for (int i = 0; i < CAPACITY; i++) {
		temp += number[i];
		temp += addBigint.number[i];
		temp += sum.number[i];
		temp += tens;
		tens = 0;
		if (temp >= 10 && temp <= 20) { //tens
			int tempTemp = temp;
			tempTemp = tempTemp % 10;
			ones = tempTemp;
			tens = 1;
		}
		else if (temp <= 9 && temp >= 0) { //ones
			ones = temp;
			tens = 0;
		}
		else if (temp >= 20) { //twenties
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
	sum.checkIfSizeisAccurate();
	return sum;
}


int bigint::operator[] (const int findAtPosition) const {
	return number[findAtPosition];
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
	this->checkIfSizeisAccurate();
	return *this;
}

bigint bigint::timesDigit(const int x) {
	bigint sum, temp;

	for (int i = 0; i < CAPACITY; ++i) {
		temp.number[i] = number[i];
	}
	//make sum of all additions
	for (int i = 0; i < x; ++i) {
		sum = sum + temp;
	}
	//set number
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = sum.number[i];
	}
	this->checkIfSizeisAccurate();
	return *this;
}

bigint bigint::timesTen(const int x) {
	//just pushes the given bigint to the left and adds a  zero at postion zero
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
	//array that counts backwards until a non zero is found
	for (int i = CAPACITY; i >= 0; --i) {
		if (number[i] > 0) {
			size = i + 1;
			break;
		}
	}
	this->checkIfSizeisAccurate();
	return *this;
}

bigint bigint::operator+(int& add) {
	bigint addBig(add);
	//make a bigint called left, a copy from this local number
	//initialize the implicit value to the temp bigint
	bigint temp(0);
	for (int i = 0; i < CAPACITY; ++i) {
		temp.number[i] = number[i];
	}
	temp = temp + addBig;
	temp.checkIfSizeisAccurate();
	return temp;
}

bigint bigint::operator-(bigint& sub) {
	if (*this >= sub) {
		//subtraction with a bigint
		bigint difference(0);

		int carryOver = 0;
		int diff = 0;
		int leftSize = size;
		int rightSize = sub.size;

		for (int i = 0; i < CAPACITY; i++) {
			//first subtract the first position, and then if there are carry overs take caree of them
			//then, itereate through each positions until done
			int rightNum = number[i];
			int leftNum = sub.number[i];
			rightNum -= carryOver;
			carryOver = 0;
			if (rightNum >= leftNum) {
				//if greater, and no carry over
				diff = rightNum -= leftNum;
				difference.number[i] = diff;
			}
			else if (rightNum < leftNum) {
				//if bigger, then carry it over
				//first find the difference
				rightNum += 10;
				diff = rightNum - leftNum;
				difference.number[i] = diff;
				carryOver += 1;
			}
		}
		difference.checkIfSizeisAccurate();
		return difference;
	} else {
		//you had a potential negative number!
		for (int i = 0; i < CAPACITY; ++i) {
			number[i] = 0;
		} size = 0;
		return *this;
	}
}

bigint bigint::operator-(int& intToSubtract) {
	bigint sub(intToSubtract);
	if (*this >= sub) {
		//subtraction with an int
		bigint temp(0);
		//copy left side
		for (int i = 0; i < CAPACITY; ++i) {
			temp.number[i] = number[i];
		}
		temp = temp - sub;
		temp.checkIfSizeisAccurate();
		return temp;
	}
	else {
		//you had a negative number!
		for (int i = 0; i < CAPACITY; ++i) {
			number[i] = 0;
		} size = 0;
		return *this;
	}
}

bigint bigint::operator-(long long& longLongToSubtract) {
	bigint sub(longLongToSubtract);
	if (*this >= sub) {
		//subtraction with an long long
		bigint temp(0);
		//copy left side
		for (int i = 0; i < CAPACITY; ++i) {
			temp.number[i] = number[i];
		}
		temp.checkIfSizeisAccurate();
		return temp;
	}
	else {
		//you had a negative number!
		for (int i = 0; i < CAPACITY; ++i) {
			number[i] = 0;
		} size = 0;
		return *this;
	}
}

bigint bigint::operator/(bigint& bigintToDivideBy) {
	//division, this will be rough division, no decimal support, everything will be floored to the divider
	bigint temp(0), zero(0);
	bigint one(1);
	for (int i = 0; i < CAPACITY; ++i) {
		temp.number[i] = number[i];
	}
	temp.checkIfSizeisAccurate();
	bigint result(0);
	do {
		temp = temp - bigintToDivideBy;
		result = result + one;
	} while (temp > zero);
	result.checkIfSizeisAccurate();
	return result;
}

bigint bigint::operator*(bigint multiplyBigint) {
	//To compute A * B
	//B[0] is 1s place, B[1] is 10s place, B[2] is 100s place, etc.
	bigint temp;
	bigint product;
	for (int i = 0; i < CAPACITY; ++i) {
		//product = product + ( (A * B[i]) * 10^i )
		bigint copy(*this);
		if (i < multiplyBigint.size) {
			if (multiplyBigint[i] > 0) {
				temp = copy.timesDigit(multiplyBigint[i]);
				bigint tmpTimesTenProduct(temp.timesTen(i));
				product = product + tmpTimesTenProduct;
			}
		}
		else {
			break;
		}
	}
	product.checkIfSizeisAccurate();
	return product;
}

bigint factorial(bigint upperBound, bigint lowerBound) {
	bigint lowerTemp(0), upperTemp(0), one(1), range(0);
	upperTemp = upperBound;
	lowerTemp = lowerBound;
	range = upperTemp - lowerTemp;
	//cant really use recursion here because of the nature of my custom type, a simple loop will do
	do {
		upperBound = upperBound - one;
		upperTemp = upperTemp * upperBound;
		range = range - one;
	} while (!(range == 0));
	upperTemp.checkIfSizeisAccurate();
	return upperTemp;
}

#endif

