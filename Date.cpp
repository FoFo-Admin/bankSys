#include "Date.h"
#include <ctime>
#include <iostream>
using namespace std;
#include <cstring>

bool Date::isLeapYear()
{
	if (year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0))
		return true;
	else
		return false;
}

int Date::monthDays()
{
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear() ?  29 :  28;
	}
	return 0;
}

void Date::nextDate()
{
	if (day == 31 && month == 12) {
		day = 1;
		month = 1;
		year++;
	}
	else if (day == monthDays()) {
		day = 1;
		month++;
	}
	else {
		day++;
	}
}

void Date::prevDate()
{
	if (day == 1 && month == 1) {
		day = 31;
		month = 12;
		year--;
	}
	else if (day == 1) {
		month--;
		day = monthDays();
	}
	else {
		day--;
	}
}

Date::Date()
{
	struct tm *tim = new tm;
	time_t tt = time(NULL);
	localtime_s(tim, &tt);

	day = tim->tm_mday;
	month = tim->tm_mon + 1;
	year = tim->tm_year + 1900;
}

Date::Date(int seconds)
{
	struct tm *tim = new tm;
	time_t tt = seconds;
	localtime_s(tim, &tt);

	day = tim->tm_mday;
	month = tim->tm_mon + 1;
	year = tim->tm_year + 1900;
}

Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

Date::Date(const Date & obj)
{
	this->day = obj.day;
	this->month = obj.month;
	this->year = obj.year;
}


Date::~Date()
{
}

void Date::setYear(int year)
{
	this->year = year;
}

int Date::getYear()
{
	return year;
}

void Date::setMonth(int month)
{
	if (month >= 1 && month <= 12) {
		this->month = month;
	}
}

int Date::getMonth()
{
	return month;
}

const char * Date::getSMonth(const char * lan)
{
	char* tmp = new char[20];
	if (strcmp(lan, "RU") == 0) {
		switch (month)
		{
		case 1: strcpy_s(tmp, 20, "€нварь"); break;
		case 2: strcpy_s(tmp, 20, "февраль"); break;
		case 3: strcpy_s(tmp, 20, "март"); break;
		case 4: strcpy_s(tmp, 20, "апрель"); break;
		case 5: strcpy_s(tmp, 20, "май"); break;
		case 6: strcpy_s(tmp, 20, "июнь"); break;
		case 7: strcpy_s(tmp, 20, "июль"); break;
		case 8: strcpy_s(tmp, 20, "август"); break;
		case 9: strcpy_s(tmp, 20, "сент€брь"); break;
		case 10: strcpy_s(tmp, 20, "окт€брь"); break;
		case 11: strcpy_s(tmp, 20, "но€брь"); break;
		case 12: strcpy_s(tmp, 20, "декабрь"); break;
		}
	}
	else if (strcmp(lan, "EN") == 0) {
		strcpy_s(tmp, 20, "month"); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	else {
		strcpy_s(tmp, 20, "not found");
	}
	return tmp;
}

void Date::setDay(int day)
{
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day >= 1 && day <= 31) {
			this->day = day;
		}
		break;
	
	case 4: case 6: case 9: case 11:
		if (day >= 1 && day <= 30) {
			this->day = day;
		}
		break;

	case 2: 
		///*if (day >= 1 && day <= (28 + isLeapYear())) {
		//	this->day = day;
		//}*/
		
		if (isLeapYear() && day >= 1 && day <= 29) {
				this->day = day;
			}
			else if (!isLeapYear() && day >= 1 && day <= 28) {
				this->day = day;
			}
			break;
	}
}

int Date::getDay()
{
	return day;
}

bool Date::valid()
{
	if (month < 0 || month>12 || day < 0 || day > 31 || year < 0)
		return false;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	else
		return true;
}

void Date::showDate()
{
	cout << year << "-" << month / 10 << month % 10 << "-"
		<< day / 10 << day % 10 << endl;
}

bool Date::operator==(const Date & obj)const&
{
	if (this->day == obj.day 
		&& this->month == obj.month 
		&& this->year == obj.year)
		return true;
	else
		return false;
}

bool Date::operator!=(const Date & obj)const&
{
	/*if (this->day != obj.day
		|| this->month != obj.month
		|| this->year != obj.year)
		return true;
	else
		return false;*/
	return !(*this == obj);
}

bool Date::operator>(const Date & obj)const&
{
	if (this->year > obj.year)
		return true;

	else if (this->year == obj.year &&
		this->month > obj.month)
		return true;

	else if (this->year == obj.year &&
		this->month == obj.month &&
		this->day > obj.day)
		return true;

	return false;
}

bool Date::operator<(const Date & obj)const&
{
	return !( *this > obj) && *this != obj;
}

bool Date::operator>=(const Date & obj)const&
{
	return *this > obj || *this == obj;
}

bool Date::operator<=(const Date & obj)const&
{
	return *this < obj || *this == obj;
}

Date & Date::operator=(const Date & obj)
{
	// TODO: insert return statement here

	//Copy constructor
	this->day = obj.day;
	this->month = obj.month;
	this->year = obj.year;

	return *this;
}

Date & Date::operator+=(int n)
{
	// TODO: insert return statement here
	for (int i = 0; i < n; i++) {
		this->nextDate();
	}
	return *this;
}

Date & Date::operator-=(int n)
{
	// TODO: insert return statement here
	for (int i = 0; i < n; i++) {
		this->prevDate();
	}
	return *this;
}

Date Date::operator+(int n)
{
	Date tmp = *this;
	for (int i = 0; i < n; i++) {
		tmp.nextDate();
	}
	return tmp;
}

Date Date::operator-(int n)
{
	Date tmp = *this;
	for (int i = 0; i < n; i++) {
		tmp.prevDate();
	}
	return tmp;
}

ostream&  operator << (ostream& out, Date& obj){
	out << obj.day / 10 << obj.day % 10 << "-"
		<< obj.month / 10 << obj.month % 10 << "-"
		<< obj.year;
	return out;
}

istream & operator>>(istream & in, Date & obj)
{
	// TODO: insert return statement here
	cout << "dd-mm-yyyy:";
	in >> obj.day >> obj.month >> obj.year;
	return in;
}
