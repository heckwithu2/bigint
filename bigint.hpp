/**
* JEREMIAH HECK
* BIGINT
* CS 23001
*/

#ifndef BIGINT_HPP_
#define BIGINT_HPP_
#include <iostream>
#include <fstream>
#include <utility>

const int CAPACITY = 400;

class bigint {
private:
	const int capacity = CAPACITY;
	//Tells how many digits there are that are not zero
	int size = 0;
	//determines the max capacity
	int number[CAPACITY] = {0};
public:
	//constructers
	bigint();
	bigint(const int&);
	bigint(const long long&);
	bigint(const char[]);
	bigint(const int[]);

	bigint(const bigint&);	
	bigint& operator=(bigint); //copy and swap
	bigint& operator=(const char[]);
	bigint& operator=(const int&);
	bigint& operator=(const long long&);
	
	//methods
	bigint timesDigit(const int);
	bigint timesTen(const int);
	void checkIfSizeisAccurate();
	void swap(bigint&);

	//accessors
	int operator[] (const int) const;
	int getSize() const;
	int getCapacity() const;

	//operator overloading
	bigint operator-(long long&) const; //no negative support
	bigint operator-(int&) const; //no negative support
	bigint operator-(bigint&) const; //no negative support
	bigint operator/(bigint&) const;//not fully functioning: IE no decimal support
	bigint operator*(bigint&) const;
	bigint operator+(int&) const;
	bigint operator+(bigint&) const;
	bool operator>(bigint&) const;
	bool operator>=(bigint&) const;
	bool operator>=(long long&) const;
	bool operator>=(int&) const;
	bool operator==(const int&) const;
	bool operator==(const bigint&) const;
	bool operator==(const char x[]) const;

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

bigint::bigint(const bigint& copy) {
	if (this != &copy) {
		size = copy.size;
		for (int i = 0; i < size; ++i) {
			number[i] = copy.number[i];
		}
	}
}

bigint::bigint(const int& numToBigint) {
	int copy = numToBigint;
	//begin determining the size of the number right to left, ones at 0, tens at 1 etc...
	int countSize = 0;
	while (copy > 0) {
		number[countSize] = copy % 10;
		copy = copy / 10;
		countSize++;
	} 
	size = countSize;
}

bigint::bigint(const long long& numToBigint) {
	long long copy = numToBigint;
	//begin determining the size of the number right to left, ones at 0, tens at 1 etc...
	int countSize = 0;
	while (copy > 0) {
		number[countSize] = copy % 10;
		copy = copy / 10;
		countSize++;
	} 
	size = countSize;
}


bigint::bigint(const int x[]) {
	for (int i = 0; i < CAPACITY; ++i) {
		number[i] = x[i];
	}
	this->checkIfSizeisAccurate();
}

bigint::bigint(const char charArrayToBigint[]) {
	//find size
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
	} 
	size = finalSize;
}

void bigint::checkIfSizeisAccurate() {
	//make sure size is correct!
	//loop that counts backwards until a non zero is found
	size = 0;
	for (int i = CAPACITY-1; i >= 0; --i) {
		if (number[i] > 0) {
			size = i + 1;
			break;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const bigint& outputThisBigint){
	for (int i = outputThisBigint.size - 1;i >= 0; --i) {
		os << outputThisBigint.number[i];
	}
	return os;
}

bool bigint::operator==(const int& checkAgainstInt) const{
	bigint rhs(checkAgainstInt);
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != rhs.number[i]) {
			return false;
		}
	} return true;
}

bool bigint::operator==(const bigint& rhs) const{
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != rhs.number[i]) {
			return false;
		}
	} return true;
}


bool bigint::operator==(const char checkAgainstCharArray[]) const{
	bigint rhs(checkAgainstCharArray);
	for (int i = 0; i < CAPACITY; ++i) {
		if (number[i] != rhs.number[i]) {
			return false;
		}
	} return true;
}

bool bigint::operator>=(bigint& rhs) const{
	bigint copy = *this;
	copy.checkIfSizeisAccurate();
	rhs.checkIfSizeisAccurate();
	//if left is bigger than right
	if (copy.size > rhs.size) {
		return true;
	}
	else if (copy.size < rhs.size) {
		return false;
	}
	if (copy.size == rhs.size) {
		for (int i = copy.size; i >= 0; --i) {
			//if same size and number
			if (copy == rhs) {
				//if same size but not same number
				if (copy.number[copy.size] > rhs.number[copy.size]) {
					return true;
				}
				else if (copy.number[copy.size] < rhs.number[copy.size]) {
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

bool bigint::operator>=(int& checkAgainstInt) const{
	bigint rhs(checkAgainstInt);
	if (*this >= rhs) {
		return true;
	} else {
		return false;
	}
}

bool bigint::operator>=(long long& checkAgainstLongLong) const{
	bigint rhs(checkAgainstLongLong);
	if (*this >= rhs) {
		return true;
	} else {
		return false;
	}
}

bool bigint::operator>(bigint& rhs) const{
	bigint copy = *this;
	copy.checkIfSizeisAccurate();
	rhs.checkIfSizeisAccurate();
	//if left is bigger than right
	if (copy.size > rhs.size) {
		return true;
	}
	else if (copy.size < rhs.size) {
		return false;
	}
	if (copy.size == rhs.size) {
		for (int i = copy.size; i >= 0; --i) {
			//if same size and number
			if (copy == rhs) {
				//if same size but not same number
				if (copy.number[copy.size] > rhs.number[copy.size]) {
					return true;
				}
				else if (copy.number[copy.size] < rhs.number[copy.size]) {
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

int bigint::getSize() const{
	return size;
}

int bigint::getCapacity() const{
	return capacity;
}
bigint bigint::operator+(bigint& addBigint) const{
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


int bigint::operator[] (const int index) const {
	return number[index];
}

bigint& bigint::operator=(const char rhs[]) {
	bigint copy = *this;
	//remove old number if present
	for (int i = 0; i < CAPACITY; ++i) {
		copy.number[i] = 0;
	}
	int size = 0;

	//make new size
	while (rhs[size] != '\0') {
		++size;
	}

	int bSize = size - 1;
	//find actual numbers?
	for (int i = 0; size > i; ++i) {
		if (rhs[i] >= 0) {
			char f = rhs[i];
			int g = f - '0';
			number[bSize] = g;
			bSize--;
		}
	}
	copy.checkIfSizeisAccurate();
	*this = copy;
	return *this;
}

bigint& bigint::operator=(bigint rhs) {
	//self assignment check
	swap(rhs);
	return *this;
}

bigint& bigint::operator=(const long long& rhs) {
	bigint copy(rhs);
	*this = copy;
	return *this;
}

bigint& bigint::operator=(const int& rhs) {
	bigint copy(rhs);
	*this = copy;
	return *this;
}

void bigint::swap(bigint& swap) {
	std::swap(size, swap.size);
	std::swap(number, swap.number);
}

bigint bigint::timesDigit(const int multiplyBy) {
	bigint sum;
	//make sum of all additions
	for (int i = 0; i < multiplyBy; ++i) {
		sum = sum + *this;
	}
	
	sum.checkIfSizeisAccurate();
	return sum;
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

bigint bigint::operator+(int& add) const{
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

bigint bigint::operator-(bigint& sub) const{
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
		//you had a negative number!
		bigint zero(0);
		return zero;
		//std::cout << "Your result is negative, this is not implemented.";
	}
}

bigint bigint::operator-(int& intToSubtract) const{
	bigint sub(intToSubtract);
	if (*this >= sub) {
		//subtraction with an int
		bigint temp(intToSubtract);
		temp = temp - sub;
		temp.checkIfSizeisAccurate();
		return temp;
	}
	else {
		//you had a negative number!
		bigint zero(0);
		return zero;
		//std::cout << "Your result is negative, this is not implemented.";
	}
}

bigint bigint::operator-(long long& longLongToSubtract) const{
	bigint sub(longLongToSubtract);
	if (*this >= sub) {
		//subtraction with an long long
		bigint temp(longLongToSubtract);
		temp = temp - sub;
		temp.checkIfSizeisAccurate();
		return temp;
	}
	else {
		//you had a negative number!
		bigint zero(0);
		return zero;
		//std::cout << "Your result is negative, this is not implemented.";
	}
}

bigint bigint::operator/(bigint& bigintToDivideBy) const{
	//division, this will be rough division, no decimal support, everything will be floored to the divider
	bigint temp(*this), zero(0);
	bigint one(1);
	bigint result(0);
	do {
		temp = temp - bigintToDivideBy;
		result = result + one;
	} while (temp > zero);
	result.checkIfSizeisAccurate();
	//std::cout << "Your result is floored potentially.";
	return result;
}

bigint bigint::operator*(bigint& multiplyBigint) const{
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
	bigint upperTemp = upperBound;
	bigint lowerTemp = lowerBound;
	bigint range = upperTemp - lowerTemp;
	bigint one(1);
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

