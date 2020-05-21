#pragma once
#ifndef COMMAND_H
#define COMMAND_H


#include <iostream>
#include "LegalFlagsCombinations.h"
#include "symbolTable.h"

using namespace std;


class Command
{
public:
	Command() {}
	virtual ~Command() {}
	virtual string execute(int format, symbolTable) = 0;
};

class findFlags : public Command {
private:
	string findNiX(string,symbolTable);
public:
	findFlags();
	~findFlags();
	string execute(int format, symbolTable);

};

class toHexa : public Command{
public:
	toHexa();
	~toHexa();
	string execute(int format, symbolTable);

};

class forwRefFound {
public:
	forwRefFound() {}
	virtual ~forwRefFound() {}
	void execute(string);
};
#endif // COMMAND_H
