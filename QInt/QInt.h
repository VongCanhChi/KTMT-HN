#pragma once
#include<iostream>
#include <string>
using namespace std;
class QInt
{
protected:
	
	int Data[4];

public:
	QInt();
	~QInt();
	int SetBit1(int&, int);
	int SetBit0(int&, int);
	int Getbit(int, int);
	string StringDecDivTwo(string&);
	string StringToBin(string);
	void ScanQInt(QInt&);

    string SummationNumberString(string, string);
    string SubtractionNumberString(string, string);
    string MultiplicationNumberString(string, string);
	string Exponentiation(int, int);
	string QIntToDec(QInt);
	void PrintQInt(QInt);

};

