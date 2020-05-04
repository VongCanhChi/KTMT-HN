#pragma once
#include "QInt.h"

class QFloat:QInt
{
public:
	QFloat();
	~QFloat();
	bool CompareString(string, string);
	string DemicalStringToBin(string);
	void SplitString(string, string&, string&);
	void Standardized(string&, string, string, int&);
	void DecToBin(int, int bin[16]);
	void SetDayBit(string&, int);
	void ScanQFloat(string, int);

	int BinToDec(int bin[15]);
	void ExponentiationNegative(int a[], int n);
	void QInttoDec(string&, string&);
	void PrintQFloat(int base);
};

