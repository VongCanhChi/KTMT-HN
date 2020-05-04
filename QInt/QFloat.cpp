#include "QFloat.h"

QFloat::QFloat():QInt()
{
}

QFloat::~QFloat()
{
}

bool QFloat::CompareString(string a, string b)
{
	if (a.size() > b.size())
	{
		return true;
	}
	if (a.size() < b.size())
	{
		return false;
	}
	if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] > b[i])
			{
				return true;
			}
			if (a[i] < b[i])
			{
				return false;
			}
		}
	}
	
}

string QFloat::DemicalStringToBin(string DemicalString)
{
	string Result;
	while (DemicalString != Exponentiation(10, DemicalString.size()))
	{
		string Temp = MultiplicationNumberString(DemicalString, "2");
		if (Temp == Exponentiation(10, DemicalString.size()))
		{
			Result.push_back('1');
			break;
		}
		if (CompareString(Temp, Exponentiation(10, DemicalString.size())) == false)
		{
			Result.push_back('0');
			DemicalString = Temp;
		}
		if (CompareString(Temp, Exponentiation(10, DemicalString.size())) == true)
		{
			Result.push_back('1');
			DemicalString = SubtractionNumberString(Temp, Exponentiation(10, DemicalString.size()));
		}
	}
	return Result;
}

void QFloat::SplitString(string a, string& b, string& c)
{
	
	if (a[0] == '-')
	{
		a.erase(a.begin());
	}
	int index = a.find(".");
	b = a.substr(0, index);
	c = a.substr(index + 1, a.size() - 1);
}

void QFloat::Standardized(string& a, string b, string c, int &Exponent)
{
	int i;
	for (i = 0; i < 112; i++) {
		if (b[i] == '1')break;
	}
	int k = 0;
	if (i <= 111) {// Nếu phần nguyên khác 0
		for (int j = i + 1; j < 112; j++) {
			a[k] = b[j];
			k++;
		}
		Exponent = k;
		for (int j = 0; j < 112; j++)
		{
			a[k] = c[j];
			k++;
		}
	}
	else {// Nếu phần nguyên bằng 0
		int j = 0;
		for (j = 0; j < 112; j++) {
			if (c[j] == 1)break;
		}
		Exponent = -j - 1;
		for (int l = j + 1; l < 112; l++)
		{
			a[k] = c[l];
			k++;
		}
	}
}

void QFloat::DecToBin(int dec, int bin[16])
{
	for (int i = 0; i < 16; i++)
	{
		bin[i] = 0;
	}
	for (int i = 15; dec > 0; i--) {
		if (dec % 2 != 0) {
			bin[i] = 1;
		}
		dec = dec / 2;
	}
}

void QFloat::SetDayBit(string& Temp, int n)
{
	for (int i = 0; i < n; i++)
	{
		Temp.push_back('0');
	}
}

void QFloat::ScanQFloat(string Number, int base)
{
	if (base == 2)
	{
		for(int i = 0; i < Number.size(); i++)
		{
			if (Number[i] == '0')
			{
				Data[i / 32] = SetBit0(Data[i / 32], i % 32);
			}
			if (Number[i] == '1')
			{
				Data[i / 32] = SetBit1(Data[i / 32], i % 32);
			}
		}
	}
	if (base == 10)
	{
		string str1, str2;
		SplitString(Number, str1, str2);
		string a;
		SetDayBit(a, 112);
		string Result = StringToBin(str1);
		int k = 0;
		for (int i = Result.size(); i >= 0; i--)
		{
			a[112 - k] = Result[i];
			k++;
		}
		string b;
		b = DemicalStringToBin(str2);
		for (int i = b.size(); i < 112; i++)
		{
			b.push_back('0');
		}
		string Temp;
		SetDayBit(Temp, 224);
		int Exponent;
		Standardized(Temp, a, b, Exponent);

		if (Number[0]) {// Nếu là số âm thì thì phần bitSign dấu bằng 1 và ngược lại
			SetBit1(Data[0], 0);
		}
		int Exp = Exponent + 16383;// Phần mũ Exponent với thừa số K = 16383 (K = 2^(15-1) - 1)
		int ExpBin[16];
		DecToBin(Exp, ExpBin);

		for (int i = 1; i < 16; i++) {
			if (ExpBin[i] == 1) {
				Data[i / 32] = SetBit1(Data[i / 32], i % 32); // Gán dãy bít vào QInt
			}
		}
		for (int i = 16; i < 128; i++) {
			if (Temp[i - 16] == '1') {
				Data[i / 32] = SetBit1(Data[i / 32], i % 32); // Gán dãy bít vào QInt
			}
		}
	}
}

int QFloat::BinToDec(int bin[15])
{
	int dec = 0;
	for (int i = 0; i < 15; i++) {
		dec = dec + bin[14 - i] * pow(2, i);
	}
	return dec;
}

void QFloat::ExponentiationNegative(int a[100],int n)
{
	a[0] = 5;
	if (n == -1) {
		return;
	}
	for (int i = 1; i < -n; i++) {
		for (int k = 0; k < 100; k++) {
			if (a[k] % 2 != 0)
				a[k + 1] += 10;
			a[k] = (a[k] / 2);
		}
	}
}

void QFloat::QInttoDec(string& a, string& b)
{
	int ExpBin[15] = { 0 };
	for (int i = 1; i < 16; i++) {
		if (Getbit(Data[i / 32], i % 32) == 1) {
			ExpBin[i - 1] = 1;
		}
	}
	int dec = BinToDec(ExpBin);
	int Exponent = dec - 16383;

	SetDayBit(a, 100);
	SetDayBit(b, 100);
	string Temp;
	SetDayBit(Temp, 100);
	string Temp1;
	SetDayBit(Temp1, 112);
	string Temp2;
	SetDayBit(Temp2, 112);
	if (Exponent < 0) {		// Nếu E < 0, tức phần nguyên bằng 0
		Temp2[-Exponent - 1] = 1;//Dãy bit của phần thập phân
		for (int i = 16; i < 112; i++) {
			Temp2[-Exponent + i - 16] = Getbit(Data[i / 32], i % 32);
		}
	}
	else {// E > 0, tức phần nguyên khác 0
		Temp1[111 - Exponent] = 1;// Dãy bit của phần nguyên
		for (int i = 16; i < 16 + Exponent; i++) {
			Temp1[i - 15 + 111 - Exponent] = Getbit(Data[i / 32], i % 32);
		}
		for (int i = 16 + Exponent; i < 112; i++) {
			Temp2[i - (16 + Exponent)] = Getbit(Data[i / 32], i % 32);//Dãy bit của phần thập phân
		}
		for (int i = 1; i < 112; i++) {// Cộng phần nguyên
			if (Temp1[i] == 1) {
				Temp = Exponentiation(2, 111 - i);
				a = SummationNumberString(a, Temp);
			}
		}
	}
	int temp3[100] = { 0 };
	for (int i = 1; i < 112; i++) {// Cộng phần thập phân
		if (Temp2[i - 1] == 1) {
			ExponentiationNegative(temp3, -i);
			string temp4;
			SetDayBit(temp4, 100);
			for (int i = 0; i < 100; i++)
			{
				temp4[i] = char(temp3[i]) + 48;
			}
			
			b = SummationNumberString(b, temp4);
		}
	}
}

void QFloat::PrintQFloat(int base)
{
	if (base == 2)
	{
		cout << Getbit(Data[0], 0) << " ";
		for (int i = 1; i < 16; i++) {
			cout << Getbit(Data[i / 32], i % 32); // In dãy QInt ra màn hình
		}
		cout << " ";
		for (int i = 16; i < 128; i++) {
			cout << Getbit(Data[i / 32], i % 32); // In dãy QInt ra màn hình
		}
	}
	if (base == 10)
	{
		string a;
		string b;
		QInttoDec(a, b);
		cout << endl;
		cout << "Dang thap phan: " << endl;
		int i = 0;
		if (Getbit(Data[0], 0)) {// In dấu trừ
			cout << "-";
		}
		for (i = 0; i < 99; i++) {// Bỏ qua các số 0 trong dãy 100 số in ra
			if (a[i] != '0') break;
		}
		for (int j = i; j < 100; j++) {
			cout << a[j];
		}
		cout << ".";
		for (int j = 0; j < 25; j++) {
			cout << b[j];
		}
	}
}
