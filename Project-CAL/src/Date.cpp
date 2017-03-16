#include "Date.h"

// Auxiliar function
bool isLeapYear(int year)
{
	bool leap_year = false;

	if (year % 400 == 0)
		leap_year = true;
	else
		if ((year % 4 == 0) && (year % 100 != 0))
			leap_year = true;

	return leap_year;
}

//-------------------------------------------------------------------------

// Auxiliar function
bool isCorrectDate(int year, int month, int day, int hour, int minute, int second)
{
	bool correct = true;

	if (month < 1 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
		correct = false;

	if (correct)
	{
		int monthDays;

		if (((month <= 7) && (month % 2 != 0)) || ((month > 7) && (month % 2 == 0)))
			monthDays = 31;
		else
			if ((month == 4) || (month == 6) || ((month >= 9) && (month % 2 != 0)))
				monthDays = 30;
			else
				if ((month == 2) && isLeapYear(year))
					monthDays = 29;
				else
					monthDays = 28;

		correct = (day >= 1 && day <= monthDays);
	}

	return correct;
}

//-------------------------------------------------------------------------

// Constructor
Date::Date(int year, int month, int day, int hour, int minute, int second)
{

	if (!isCorrectDate(year, month, day, hour, minute, second))
		throw InvalidDate();

	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

//-------------------------------------------------------------------------

Date::Date(time_t &time)
{
	char t[50];
	ctime_s(t, 50, &time);

	std::stringstream time_ss;
	for (size_t i = 0; i < 50; i++)
		time_ss << t[i];

	int y, mon, day, h, min, s;
	std::string weekDay, month;
	char ch;
	time_ss >> weekDay >> month >> day >> h >> ch >> min >> ch >> s >> y;

	if (month == "Jan")
		mon = 1;
	else if (month == "Feb")
		mon = 2;
	else if (month == "Mar")
		mon = 3;
	else if (month == "Apr")
		mon = 4;
	else if (month == "May")
		mon = 5;
	else if (month == "Jun")
		month = 6;
	else if (month == "Jul")
		mon = 7;
	else if (month == "Aug")
		month = 8;
	else if (month == "Sep")
		mon = 9;
	else if (month == "Oct")
		month = 10;
	else if (month == "Nov")
		mon = 11;
	else if (month == "Dec")
		mon = 12;

	if (!isCorrectDate(y, mon, day, h, min, s))
		throw InvalidDate();

	this->year = y;
	this->month = mon;
	this->day = day;
	this->hour = h;
	this->minute = min;
	this->second = s;
}

//-------------------------------------------------------------------------

// Get methods
int Date::getYear() const
{
	return year;
}

//-------------------------------------------------------------------------

int Date::getMonth() const
{
	return month;
}

//-------------------------------------------------------------------------

int Date::getDay() const
{
	return day;
}

//-------------------------------------------------------------------------

int Date::getHour() const
{
	return hour;
}

//-------------------------------------------------------------------------

int Date::getMinute() const
{
	return minute;
}

//-------------------------------------------------------------------------

int Date::getSecond() const
{
	return second;
}

//-------------------------------------------------------------------------

bool Date::operator<(const Date &d) const
{
	bool test = false;

	if (year < d.year)
		test = true;
	else if (year == d.year)
	{
		if (month < d.month)
			test = true;
		else if (month == d.month)
		{
			if (day < d.day)
				test = true;
			else if (day == d.day)
			{
				if (hour < d.hour)
					test = true;
				else if (hour == d.hour) {
					if (minute < d.minute)
						test = true;
					else if (minute == d.minute)
						if (second < d.second)
							test = true;
				}
			}
		}
	}

	return test;
}

//-------------------------------------------------------------------------

bool Date::operator>(const Date &d) const
{
	return (!operator<(d) && !operator==(d));
}

bool Date::operator==(const Date &d) const
{
	return (year == d.year) && (month == d.month) && (day == d.day) && (hour == d.hour) && (minute == d.minute) && (second == d.second);
}

//-------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& out, const Date* d)
{
	out << d->getYear() << "/" << d->getMonth() << "/" << d->getDay() << " " << d->getHour() << ":" << d->getMinute() << ":" << d->getSecond();
	return out;
}
