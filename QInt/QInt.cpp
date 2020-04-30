#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
	{
		Data[i] = 0;
	}
}

QInt::~QInt()
{
}

int QInt::SetBit1(int &x, int i)
{
	return x | (1 << (31 - i));
}

int QInt::SetBit0(int& x, int i)
{
	return (~(1 << (31 - i))) & x;
}

int QInt::Getbit(int x, int i)
{
	return (x >> (31 - i)) & 1;
}

string QInt::StringDecDivTwo(string& StringDec)
{
	string Result;
	int Temp = 0;

	for (int i = 0; i < StringDec.size(); i++)
	{
		Temp = Temp * 10 + (StringDec[i] - '0');

		if (i > 0 || (i == 0 && Temp >= 2))
		{
			Result.push_back((Temp / 2) + '0');
		}

		Temp = Temp % 2;
	}
	return Result;
}

string QInt::StringToBin(string StringDec)
{
	string Result;
	bool Negative = false;
	if (StringDec[0] == '-') 
	{
		StringDec.erase(StringDec.begin());
		Negative = true;
	}
	while (StringDec != "")
	{
		Result.push_back(((StringDec[StringDec.size() - 1] - '0') % 2) + '0');
		StringDec = StringDecDivTwo(StringDec);
	}
	reverse(Result.begin(), Result.end());
	if (Negative == true)
	{
		int length = 128 - Result.size();
		string a;
		for (int i = 0; i < length; i++)
		{
			a.push_back('1');
		}
		for (int i = Result.size() - 1; i >= 0; i--)
		{
			if (Result[i] == '1')
			{
				for (int j = i - 1; j >= 0; j--)
				{
					if (Result[j] == '1')
					{
						Result[j] = '0';
					}
					else
					{
						Result[j] = '1';
					}
				}
				break;
			}
		}
		Result = a + Result;
	}
	return Result;
}

void QInt::ScanQInt(QInt& x)
{
	string StringDec;
	cout << "Nhap: ";
	cin >> StringDec;
	string StringBin = StringToBin(StringDec);
	int k = 127;
	for (int i = StringBin.size() - 1; i >= 0; i--)
	{
		if (StringBin[i] == '0')
		{
			x.Data[k / 32] = SetBit0(x.Data[k / 32], k % 32);
			k--;
		}
		if (StringBin[i] == '1')
		{
			x.Data[k / 32] = SetBit1(x.Data[k / 32], k % 32);
			k--;
		}
	}
}

void QInt::PrintQInt(QInt x)
{
	for (int i = 0; i < 128; i++)
	{
		cout << x.Getbit(x.Data[i / 32], i % 32);
	}
}
