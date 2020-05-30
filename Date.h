#pragma once
#include <iostream>
using namespace std;

class Date
{
	int year;
	int month;
	int day;

	bool isLeapYear(); 
	int monthDays();  
	void nextDate();  
	void prevDate();  

public:
	 
	Date(); 
	Date(int seconds);
	Date(int year, int month, int day);  
	Date(const Date& obj);  
	~Date(); 

			 
	void setYear(int year);
	int getYear();
	void setMonth(int month);
	int getMonth();
	const char* getSMonth(const char* lan = "EN");
	void setDay(int day);
	int getDay();

	bool valid();  
	void showDate();

	//--------- Comparison operators ---------
	bool operator == (const Date&  obj)const&;
	bool operator != (const Date& obj)const&;
	bool operator > (const Date& obj)const&;
	bool operator < (const Date& obj)const&;
	bool operator >= (const Date& obj)const&;
	bool operator <= (const Date& obj)const&;

	//--------- Assignment operators ---------
	Date& operator = (const Date& obj);
	Date& operator += (int n);
	Date& operator -= (int n);

	//--------- Arithmetic operators ---------
	Date operator + (int n);
	Date operator - (int n);

	friend ostream& operator << (ostream& out, Date& obj);
	friend istream& operator >> (istream& in, Date& obj);
};

