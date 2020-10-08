#include <iostream>
using namespace std;

bool LeapYear(int nam)
{
	if (nam % 400 == 0) return true;
	else if (nam % 100 != 0 && nam % 4 == 0) return true;
	else return false;
}

void NextDay(int& ngay, int& thang, int& nam)
{
	int a[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (LeapYear(nam)) a[1] = 29;
	int dayMax = a[thang - 1];
	ngay++;
	if (ngay < dayMax) return;
	else if (ngay > dayMax)
	{
		ngay = 1;
		thang++;
		if (thang < 12) return;
		else if (thang > 12)
		{
			thang = 1;
			nam++;
			return;
		}
		return;
	}
}

class Ngay
{
private:
	int day, month, year;
public:
	Ngay();
	Ngay(int, int, int);
	Ngay(int);
	Ngay operator+(const Ngay&);
	Ngay operator-(const Ngay&);
	friend Ngay operator+(const int&, const Ngay&);
	friend Ngay operator-(const int&, const Ngay&);
	friend bool operator>(const Ngay&, const Ngay&);
	void Xuat();
	bool LeapYear(int);
	int FindDay(int, int, int&);
	void CountDay(int);
};

Ngay::Ngay()
{
	day = 1;
	month = 1;
	year = 1;
}

Ngay::Ngay(int ngay, int thang, int nam)
{
	if (thang < 1) thang = 1;
	else if (thang > 12)
	{
		thang = thang - 12;
		nam++;
	}
	if (ngay < 1) ngay = abs(ngay);
	else if (ngay > 31)
	{
		int temp = 0;
		switch (thang)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: temp = 31;
		case 4:
		case 6:
		case 9:
		case 11: temp = 30;
		case 2:
			if (LeapYear(nam)) temp = 29;
			else temp = 28;
		}
		ngay = temp;
	}
	day = ngay;
	month = thang;
	year = nam;
}

Ngay::Ngay(int value)
{
	int nam = 1;
	int thang = 1;
	while (true)
	{
		if (LeapYear(nam))
		{
			if (value > 366) value -= 366;
			else
			{
				day = FindDay(nam, value, thang);
				month = thang;
				year = nam;
				return;
			}
		}
		else
		{
			if (value > 365) value -= 365;
			else
			{
				day = FindDay(nam, value, thang);
				month = thang;
				year = nam;
				return;
			}
		}
		nam++;
	}
}

Ngay Ngay::operator+(const Ngay& P)
{
	Ngay now = *this;
	now.day += P.day;
	now.month += P.month;
	now.year += P.year;
	if (now.month > 12)
	{
		now.month -= 12;
		now.year++;
	}
	return now;
}

Ngay Ngay::operator-(const Ngay& P)
{
	Ngay now = *this;
	now.day -= P.day;
	now.month -= P.month;
	now.year -= P.year;
	if (now.day < 1) now.day = 1;
	if (now.month < 1)
	{
		now.month += 12;
		now.year--;
	}
	return now;
}

Ngay operator+(const int& n, const Ngay& P)
{
	Ngay now;
	now.day = n + P.day;
	now.month = P.month;
	now.year = P.year;
	for (int i = 0; i < n; i++)
		NextDay(now.day, now.month, now.year);
	return now;
}

Ngay operator-(const int& n, const Ngay& P)
{
	Ngay now;
	Ngay temp(n);
	{
		if (temp.year < P.year)
		{
			now.day = 0;
			now.month = 0;
			now.year = 0;
			return now;
		}
		else if (temp.year == P.year)
			if (temp.month < P.month)
			{
				now.day = 0;
				now.month = 0;
				now.year = 0;
				return now;
			}
			else if (temp.month == P.month)
				if (temp.day <= P.day)
				{
					now.day = 0;
					now.month = 0;
					now.year = 0;
					return now;
				}
	}
	now.year = temp.year - P.year;
	if (temp.day >= P.day) now.day = temp.day - P.day;
	else
	{
		int a[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (LeapYear(temp.year)) a[1] = 29;
		temp.day += a[temp.month - 1];
		int tempM = P.month + 1;
		now.day = temp.day - P.day;
		if (temp.month >= P.month) now.month = temp.month - P.month;
		else
		{
			now.month = 12 + temp.month - P.month;
			now.year--;
		}
	}
	return now;
}

bool operator>(const Ngay& D1, const Ngay& D2)
{
	int t1 = D1.year * 365 + D1.month * 30 + D1.day;
	int t2 = D2.year * 365 + D2.month * 30 + D2.day;
	if (t1 > t2) return true;
	else return false;
}

bool Ngay::LeapYear(int nam)
{
	if (nam % 400 == 0) return true;
	else if (nam % 100 != 0 && nam % 4 == 0) return true;
	else return false;
}

int Ngay::FindDay(int nam, int k, int& thang)
{
	int a[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (LeapYear(nam)) a[1] = 29;
	for (int i = 0; i < 12; i++)
	{
		if (k > a[i]) k -= a[i];
		else
		{
			thang = i + 1;
			return k;
		}
	}
	return k;
}

void Ngay::Xuat()
{
	cout << day << '/' << month << '/' << year << endl;
}

void main()
{
	Ngay n1;
	n1.Xuat();
	Ngay n2(2, 10, 2014);
	n2.Xuat();
	Ngay n3(-10, 16, 2000);
	n3.Xuat();
	Ngay n4(1000);
	n4.Xuat();
	Ngay n5 = n2 + n3;
	n5.Xuat();
	Ngay n6 = n1 + 5000;
	n6.Xuat();
	Ngay n7 = 1234 + n4;
	n7.Xuat();
	Ngay n8 = 190 + n6 + n7;
	n8.Xuat();
	Ngay n9 = n8 - n6;
	n9.Xuat();
	Ngay n10 = 12000 - n9;
	n10.Xuat();
	if (n10 > n6)
		n10 = n2 - 10000 + n6;
	n10.Xuat();
}