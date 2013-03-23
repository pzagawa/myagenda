/*
 * File:   TimeValue.h
 * Author: piotr
 *
 * Created on June 26, 2012, 12:42 AM
 */

#pragma once

#include <gtkmm.h>
#include <glibmm/datetime.h>
#include <string>

class TimeValue
{
private:
	int hours;
	int minutes;
	char buff[16];

public:
	TimeValue();
	TimeValue(const TimeValue& orig);
	TimeValue(Glib::DateTime& value);
	TimeValue(long value);
	virtual ~TimeValue();
	static TimeValue now();

public:
	TimeValue& operator=(const TimeValue& orig);
	bool operator==(const TimeValue& orig);
	long getHashCode() const;
	std::string getHashCodeText();
	int getHours();
	int getMinutes();
	void parseHashCode(long value);
	bool parseString(std::string value);
	void set(int hours, int minutes);
	void set(Glib::DateTime value);
	std::string toString();

};

class DateValue
{
private:
	int day;
	int month;
	int year;
	char buff[32];

public:
	DateValue();
	DateValue(const DateValue& orig);
	DateValue(const Glib::Date& value);
	DateValue(long value);
	virtual ~DateValue();
	static DateValue now();

public:
	DateValue& operator=(const DateValue& orig);
	bool operator==(const DateValue& orig);
	long getHashCode() const;
	std::string getHashCodeText();
	int getYear();
	int getMonth();
	int getDay();
	void parseHashCode(long value);
	bool parseString(std::string value);
	void set(int year, int month, int day);
	void set(Glib::Date date);
	std::string toString();

};

class DateTimeValue
{
private:
	DateValue date;
	TimeValue time;

public:
	DateTimeValue();
	static DateTimeValue now();
	static DateTimeValue zero();

	std::string toString();
	long getHashCode() const;
	std::string getHashCodeText();

};
