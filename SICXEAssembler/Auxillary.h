#pragma once
#ifndef AUXILLARY_H
#define AUXILLARY_H

#include <iostream>

using namespace std;

class transitions {

public:
	transitions() = default;
	virtual ~transitions() {}
	string subtract(string ,string ,int);
	string decimalToBinary(int);
	string hexaToBinary(string);
	int hexaToDec(string);
	int twoscomp(int, int);
	bool isOutOfRange(string);
	string add(string s1, string s2);
};

class ConvertToHexa
{
public:
	ConvertToHexa();
	std::string IntToHexa(int address);
	int hexaToInt(std::string hexa);

protected:

private:
};

class ConvertHexaToBinary
{
public:
	ConvertHexaToBinary();
	std::string hexaToBinary(std::string hexa);
protected:

private:
};

#endif // AUXILLARY_H
