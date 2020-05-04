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

string QInt::SummationNumberString(string Number1, string Number2)
{
	if (Number1[0] == '-' && Number2[0] != '-')
	{
		Number1.erase(Number1.begin());
		Number1 = SubtractionNumberString(Number2, Number1);
	}
	else
	{
		if (Number2[0] == '-' && Number1[0] != '-')
		{
			Number2.erase(Number2.begin());
			Number1 = SubtractionNumberString(Number1, Number2);
		}
		else
		{
			int Temp = 0;
			bool Negative = false;

			if (Number1[0] == '-' && Number2[0] == '-')
			{
				Negative = true;
			}
			if (Number1.size() > Number2.size())
			{
				while (Number1.size() != Number2.size())
				{
					Number2.insert(Number2.begin(), '0');
				}
			}
			else
			{
				while (Number1.size() != Number2.size())
				{
					Number1.insert(Number1.begin(), '0');
				}
			}

		
			for (int i = Number1.size() - 1; i > -1; i--)
			{
				Temp = Temp + Number1[i] + Number2[i] - 2 * '0';
				Number1[i] = (Temp % 10) + '0';
				Temp = Temp / 10;
			}

		
			if (Temp != 0)
			{
				Number1.insert(Number1.begin(), Temp + '0');
				Temp = 0;
			}
		}
		return Number1;
	}
}

string QInt::SubtractionNumberString(string Number1, string Number2)
{
	int Temp = 0;
	bool Negative = false;

	
	if (Number1.size() > Number2.size())
	{
		while (Number1.size() != Number2.size())
		{
			Number2.insert(Number2.begin(), '0');
		}
	}
	else
	{
		while (Number1.size() != Number2.size())
		{
			Number1.insert(Number1.begin(), '0');
		}
	}


	if (strcmp(Number1.c_str(), Number2.c_str()) < 0)
	{
		string TempStr = Number1;
		Number1 = Number2;
		Number2 = TempStr;
		Negative = true; 
	}

	//Thực hiện phép trừ.
	for (int i = Number1.size() - 1; i > -1; i--)
	{
		if ((Number1[i] - Temp) < Number2[i])
		{
			Number1[i] = (10 + Number1[i] - Number2[i] - Temp) + '0';
			Temp = 1;
		}
		else
		{
			Number1[i] = Number1[i] - Number2[i] - Temp + '0';
			Temp = 0;
		}
	}


	while (Number1[0] == '0')
	{
		Number1.erase(Number1.begin());
	}

	if (Negative == true)
	{
		Number1.insert(Number1.begin(), '-');
	}
	return Number1;
}

string QInt::MultiplicationNumberString(string Number1, string Number2)
{
	string Result = "0";
	string TempStr;
	int Temp = 0;
	bool Negative = false;

	if (Number1[0] == '-')
	{
		if (Number2[0] != '-')
		{
			Negative = true;
		}
		Number1.erase(Number1.begin());
	}
	if (Number2[0] == '-')
	{
		if (Number1[0] != '-')
		{
			Negative = true;
		}
		Number2.erase(Number2.begin());
	}

	for (int i = 0; i < Number2.size(); i++)
	{
		for (int j = Number1.size() - 1; j > -1; j--)
		{
			Temp = Temp + (Number1[j] - '0') * (Number2[Number2.size() - i - 1] - '0');
			TempStr.push_back((Temp % 10) + '0');
			Temp = Temp / 10;
		}
		if (Temp != 0) //Nếu vẫn còn Temp.
		{
			TempStr.push_back(Temp + '0');
			Temp = 0;
		}

		//Đảo chuỗi.
		reverse(TempStr.begin(), TempStr.end());

		//Thêm các số 0 cần thiết vào sau.
		for (int j = 0; j < i; j++)
		{
			TempStr.push_back('0');
		}

		//Cộng Result và Temp.
		Result = SummationNumberString(Result, TempStr);
		TempStr.clear(); //Dọn chuỗi tạm để dùng cho các bước tiếp theo.
	}

	if (Negative == true)
	{
		Result.insert(Result.begin(), '-');
	}

	return Result;
}

string QInt::Exponentiation(int Number , int n)
{
	string Result;
	if (n == 0)
	{
		Result = '1';
	}
	if (n == 1)
	{
		Result = to_string(Number);
	}
	if (n > 1)
	{
		Result = MultiplicationNumberString(to_string(Number), to_string(Number));
		for (int i = 3; i <= n; i++)
		{
			Result = MultiplicationNumberString(Result, to_string(Number));
		}
	}
	return Result;
}

string QInt::QIntToDec(QInt x)
{
	string Result = "0";
	if (x.Getbit(x.Data[0], 0) == 1)
	{
		Result = Exponentiation(2, 127);
		for (int i = 1; i <= 127; i++)
		{
			if (x.Getbit(x.Data[i / 32], i % 32) == 1)
			{
				Result = x.SubtractionNumberString(Result, Exponentiation(2, 127-i));
			}
		}
		Result = "-" + Result;
	}
	else
	{
		for (int i = 127; i >= 0; i--)
		{
			if (x.Getbit(x.Data[i / 32], i % 32) == 1)
			{
				Result = x.SummationNumberString(Result, Exponentiation(2, -i + 127));
			}
		}
	}
	
	return Result;
}

void QInt::PrintQInt(QInt x)
{
	for (int i = 0; i < 128; i++)
	{
		cout << x.Getbit(x.Data[i / 32], i % 32);
	}
	cout << endl << x.QIntToDec(x);
}
