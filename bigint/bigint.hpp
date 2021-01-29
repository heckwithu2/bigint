#pragma once

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
	int number[CAPACITY];
public:
	//constructers
	bigint();
	bigint(int);
	bigint(const char[]);
	bigint(int[]);
	//methods/friends
	bigint timesDigit(const int);
	bigint timesTen(const int);
	bigint operator*(bigint& B);

	bigint operator=(char []);
	int operator[] (const int index) const;
	bigint operator+(bigint&);
	bool operator==(int v);
	bool operator==(bigint &x);
	bool operator==(const char x[]);
	friend std::ostream& operator<<(std::ostream& os, const bigint& bigint);
};

#endif

