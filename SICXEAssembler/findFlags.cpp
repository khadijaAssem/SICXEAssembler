#include "Command.h"
#include "LegalFlagsCombinations.h"
#include "Auxillary.h"
#include <iostream> 
#include <sstream> 
#include "symbolTable.h"
#include "LocationsTable.h"

//using namespace std;

findFlags::findFlags()
{
	//ctor -- i.e Constructor
	cout << "Command findFlags Object is being created" << endl;
}

legalFlagsCombinations* l = l->getInstance();
transitions* t = new transitions();
string address;
string displacement;
SYMTable* table = table->getInstance();
bool forRef = false;
bool isLabel = false;

string findFlags::execute(int format, symbolTable* tableObject) {
	string opCode;
	string NIX;
	string BPE;
	cout << "executing findFlags " << endl;
	cout << "OPCode Was " << (*tableObject).getOpcode() << endl;
	cout << "PC " << (*tableObject).getNextAddress() << endl;
	NIX = findNiX((*tableObject).getOperand(), tableObject);
	if (forRef) return opCode + NIX;
	if (format == 3) {
		//IF BASE LESSA
		//if (isLabel) {
			string intermediate = t->subtract(address, (*tableObject).getNextAddress(), 12);
			if (t->isOutOfRange(intermediate)) {
				BPE = l->getBPE("Base");
				cout << "OUT OF RANGE" << endl;
				intermediate = t->subtract(address, table->getBASE(), 12);
				displacement = intermediate;//should be binary
				if (t->isOutOfRange(intermediate)) {
					(*tableObject).setError(true);
					BPE = "000";
				}
			}
			else {
				BPE = l->getBPE("PC");
				displacement = intermediate;//should be binary
			}
		//}
	//	cout << "INTERMEDIATE " << intermediate << endl;
	}
	else if (format == 4) {
		BPE = l->getBPE("address");
		displacement = address;
	}
	opCode = NIX + BPE+ displacement;
	cout << "FROM FIND FLAGS THE OPCODE IS " << opCode << "\n" << endl;
	return opCode;
}

string findFlags::findNiX(string operand,symbolTable* tableObject) {
	SYMTable* table = table->getInstance();
	
	string NIX;
	cout << "FINDING NIX" << endl;
	if (operand.find("#") < operand.size()) {
		NIX = l->getNIX("immediate");
		operand = operand.substr(1, operand.size() - 1);
		stringstream geek(operand);
		int x = 0;
		geek >> x;
		address = t->decimalToBinary(x);
		t->addZeroes(address,3);
		cout << "Address is " << address;
		forRef = false;
	}
	else if(!table->isFound(operand)){
		if (operand.find("@") < operand.size()) {
			NIX = l->getNIX("indirect");
			operand = operand.substr(1, operand.size() - 1);
			address = table->getLine(operand).getAddress();
			forRef = false;
		}
		else if (operand.find(",") < operand.size()) {
			NIX = l->getNIX("directIndexing");
			operand = operand.substr(0, operand.find(","));
			address = table->getLine(operand).getAddress();
			forRef = false;
		}
		else {
			NIX = l->getNIX("directNoIndexing");
			address = table->getLine(operand).getAddress();
			forRef = false;
		}
	}
	else if (!operand.length() == 0){
		cout << "NOT FOUND :( Forward Zift" << endl;
		Locations* lo = lo->getInstance();
		if (!lo->isFound(operand)) {
			LocationObject* ob = new LocationObject();
			ob->setStar("*");
			ob->addInVector((string)((*tableObject).getAddress()));
			//ob->getVector().push_back();
			if(operand.at(0) == '#'||operand.at(0) == '@') operand = operand.substr(1, operand.size() - 1);
			lo->addLocation(operand, *ob);
		}
		else {
			lo->getLabel(operand).getVector().push_back((*tableObject).getAddress());
		}
		forRef = true;
		NIX = l->getNIX("directNoIndexing");
	}

	cout << "adress is " << address << " and NIX is "<<NIX<<endl;
	return NIX;
}

findFlags::~findFlags()
{
	//dtor -- i.e distructor
	cout << "Command findFlags Object is being deleted" << endl;
	delete l;
	delete t;
	//delete r;
}
