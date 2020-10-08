#include <iostream>
using namespace std;

class Time
{
private:
	int hour;
	int minute;
	int sec;
public:
	Time();
	Time(int);
	Time(int, int);
	Time(int, int, int);
	Time operator+(const Time&);
	Time operator-(const Time&);
	friend Time operator+(const int&, const Time&);
	friend Time operator-(const int&, const Time&);
	friend bool operator<=(const Time&, const Time&);
	friend bool operator<=(const int&, const Time&);
	void Xuat();
};

Time::Time()
{
	hour = 0;
	minute = 0;
	sec = 0;
}

Time::Time(int giay)
{
	hour = 0;
	minute = 0;
	sec = giay;
	while (sec >= 60)
	{
		sec -= 60;
		minute++;
	}
	while (minute >= 60)
	{
		minute -= 60;
		hour++;
	}
}

Time::Time(int phut, int giay)
{
	hour = 0;
	if (giay < 0) sec = 0;
	else sec = giay % 60;
	if (phut < 0) minute = 0;
	else if (phut < 60) minute = phut;
	else
	{
		hour = phut / 60;
		minute = phut % 60;
	}
}

Time::Time(int gio, int phut, int giay)
{
	gio = abs(gio);
	phut = abs(phut);
	giay = abs(giay);
	sec = giay;
	minute = phut;
	hour = gio;
	if (sec >= 60)
	{
		minute += sec / 60;
		sec = sec % 60;
	}
	if (minute >= 60)
	{
		hour += minute / 60;
		minute = minute % 60;
	}
}

Time Time::operator+(const Time& T)
{
	Time now = *this;
	int s = abs(T.sec);
	int m = abs(T.minute);
	int h = abs(T.hour);
	now.sec += s;
	now.minute += m;
	now.hour += h;
	if (now.sec >= 60)
	{
		now.minute += now.sec / 60;
		now.sec %= 60;
	}
	if (now.minute >= 60)
	{
		now.hour += now.minute / 60;
		now.minute %= 60;
	}
	return now;
}

Time operator+(const int& n, const Time& T)
{
	Time temp(n);
	Time now;
	now.sec = temp.sec + T.sec;
	now.minute = temp.minute + T.minute;
	now.hour = temp.hour + T.hour;
	while (now.sec >= 60)
	{
		now.minute++;
		now.sec -= 60;
	}
	while (now.minute >= 60)
	{
		now.hour++;
		now.minute -= 60;
	}
	return now;
}

Time Time::operator-(const Time& T)
{
	Time now = *this;
	now.sec -= T.sec;
	now.minute -= T.minute;
	now.hour -= T.hour;
	while (now.sec < 0)
	{
		now.sec += 60;
		now.minute--;
	}
	while (now.minute < 60)
	{
		now.minute += 60;
		now.hour--;
	}
	if (now.sec >= 60)
	{
		now.minute += now.sec / 60;
		now.sec %= 60;
	}
	if (now.minute >= 60)
	{
		now.hour += now.minute / 60;
		now.minute %= 60;
	}
	return now;
}

Time operator-(const int& n, const Time& T)
{
	Time temp(n);
	Time now;
	signed int t;
	t = (temp.hour - T.hour) * 3600 + (temp.minute - T.minute) * 60 + (temp.sec - T.sec);
	if (t < 0)
	{
		now.hour = 0;
		now.minute = 0;
		now.sec = 0;
	}
	else
	{
		now.hour = t / 3600;
		now.minute = t / 60;
		now.sec = t % 60;
	}
	return now;
}

bool operator<=(const Time& T1, const Time& T2)
{
	signed int t;
	t = (T1.hour - T2.hour) * 3600 + (T1.minute - T2.minute) * 60 + (T1.sec - T2.sec);
	if (t <= 0) return true;
	else return false;
}

bool operator<=(const int& n, const Time& T)
{
	Time temp(n);
	signed int t;
	t = (temp.hour - T.hour) * 3600 + (temp.minute - T.minute) * 60 + (temp.sec - T.sec);
	if (t <= 0) return true;
	else return false;
}

void Time::Xuat()
{
	if (hour < 10) cout << '0' << hour << ':'; else cout << hour << ':';
	if (minute < 10) cout << '0' << minute << ':'; else cout << minute << ':';
	if (sec < 10) cout << '0' << sec << endl; else cout << sec << endl;
}

void main()
{
	Time t1;
	t1.Xuat();
	Time t2(1212);
	t2.Xuat();
	Time t3(125, 45);
	t3.Xuat();
	Time t4(12, 239, -78);
	t4.Xuat();
	Time t5 = t2 + t3;
	t5.Xuat();
	Time t6 = 5000 + t2;
	t6.Xuat();
	Time t7 = t4 - t6;
	t7.Xuat();
	Time t8 = 12300 - t4;
	t8.Xuat();
	Time t9, t10;
	if (t8 <= t3)
		t9 =  t2 + 36000;
	t9.Xuat();
	if (12345 <= t5)
		t10 = t5 + 12345;
	t10.Xuat();
}