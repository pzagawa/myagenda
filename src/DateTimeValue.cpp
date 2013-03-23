/*
 * File:   TimeValue.cpp
 * Author: piotr
 *
 * Created on June 26, 2012, 12:42 AM
 */

#include "Utils.h"


#include "DateTimeValue.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <glibmm-2.4/glibmm/ustring.h>
#include <glibmm-2.4/glibmm/date.h>

//TimeValue
TimeValue::TimeValue()
{
	hours = 0;
	minutes = 0;
}

TimeValue::TimeValue(const TimeValue& orig)
{
	this->hours = orig.hours;
	this->minutes = orig.minutes;
}

TimeValue::TimeValue(Glib::DateTime& value)
{
    set(value);
}

TimeValue::TimeValue(long value)
{
    parseHashCode(value);
}

TimeValue::~TimeValue()
{
}

TimeValue TimeValue::now()
{
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    TimeValue value;
    value.set(0, 0);
    value.set(timeinfo->tm_hour, timeinfo->tm_min);

    return value;
}

TimeValue& TimeValue::operator=(const TimeValue& orig)
{
    if (this == &orig)
      return *this;

	this->hours = orig.hours;
	this->minutes = orig.minutes;

    return *this;
}

bool TimeValue::operator==(const TimeValue& orig)
{
    if (this->hours == orig.hours)
        if (this->minutes == orig.minutes)
            return true;

    return false;
}

long TimeValue::getHashCode() const
{
    return (hours * 100) + minutes;
}

std::string TimeValue::getHashCodeText()
{
    std::sprintf(buff, "%ld", getHashCode());
    return buff;
}

int TimeValue::getHours()
{
    return hours;
}

int TimeValue::getMinutes()
{
    return minutes;
}

void TimeValue::parseHashCode(long value)
{
    this->hours = 0;
    this->minutes = 0;

    if (value < 0)
        return;

    if (value > 2359)
        return;

    this->hours = value / 100;
    this->minutes = value - (hours * 100);
}

//time format: ISO 8601
//"hh:mm"
bool TimeValue::parseString(std::string value)
{
    if (value.length() == 5)
    {
        std::size_t colon = value.find(":", 0);

        std::string str_hours = value.substr(0, 2);
        std::string str_minutes = value.substr(colon + 1, 2);

        int result_hours = std::atoi(str_hours.c_str());
        int result_minutes = std::atoi(str_minutes.c_str());

        if (result_hours < 0 || result_hours > 23)
            return false;

        if (result_minutes < 0 || result_minutes > 59)
            return false;

        this->hours = result_hours;
        this->minutes = result_minutes;

        return true;
    }

    return false;
}

std::string TimeValue::toString()
{
    std::sprintf(buff, "%02d:%02d", hours, minutes);
    return buff;
}

void TimeValue::set(int hours, int minutes)
{
    this->hours = hours;
    this->minutes = minutes;
}

void TimeValue::set(Glib::DateTime value)
{
    this->hours = value.get_hour();
    this->minutes = value.get_minute();
}

//DateValue
DateValue::DateValue()
{
	day = 0;
	month = 0;
	year = 0;
}

DateValue::DateValue(const DateValue& orig)
{
    this->day = orig.day;
	this->month = orig.month;
	this->year = orig.year;
}

DateValue::DateValue(const Glib::Date& value)
{
    set(value);
}

DateValue::DateValue(long value)
{
    parseHashCode(value);
}

DateValue::~DateValue()
{
}

DateValue DateValue::now()
{
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    DateValue value;
    value.set(1900 + timeinfo->tm_year, timeinfo->tm_mon + 1, timeinfo->tm_mday);

    return value;
}

DateValue& DateValue::operator=(const DateValue& orig)
{
    if (this == &orig)
      return *this;

    this->day = orig.day;
	this->month = orig.month;
	this->year = orig.year;

    return *this;
}

bool DateValue::operator==(const DateValue& orig)
{
    if (this->day == orig.day)
        if (this->month == orig.month)
            if (this->year == orig.year)
                return true;

    return false;
}

long DateValue::getHashCode() const
{
    return (year * 10000) + (month * 100) + day;
}

std::string DateValue::getHashCodeText()
{
    std::sprintf(buff, "%ld", getHashCode());
    return buff;
}

int DateValue::getYear()
{
    return year;
}

int DateValue::getMonth()
{
    return month;
}

int DateValue::getDay()
{
    return day;
}

void DateValue::parseHashCode(long value)
{
	this->day = 0;
	this->month = 0;
	this->year = 0;

    if (value < 20000101)
        return;

    if (value > 21000101)
        return;

    this->year = value / 10000;

    long month_day = value - (year * 10000);

    this->month = month_day / 100;
    this->day = month_day - (month * 100);
}

//date format: ISO 8601
//"YYYY-MM-DD"
bool DateValue::parseString(std::string value)
{
    if (value.length() == 10)
    {
        std::size_t dash1 = value.find("-", 0);
        std::size_t dash2 = value.find("-", dash1 + 1);

        std::string str_year = value.substr(0, 4);
        std::string str_month = value.substr(dash1 + 1, 2);
        std::string str_day = value.substr(dash2 + 1, 2);

        int result_year = std::atoi(str_year.c_str());
        int result_month = std::atoi(str_month.c_str());
        int result_day = std::atoi(str_day.c_str());

        if (result_year == 0)
            return false;

        if (result_month == 0)
            return false;

        if (result_day == 0)
            return false;

        if (result_day > 31)
            return false;

        if (result_month > 12)
            return false;

        if (result_year < 2000)
            return false;

        this->year = result_year;
        this->month = result_month;
        this->day = result_day;

        return true;
    }

    return false;
}

std::string DateValue::toString()
{
    std::sprintf(buff, "%04d-%02d-%02d", year, month, day);
    return buff;
}

void DateValue::set(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

void DateValue::set(Glib::Date date)
{
    this->year = date.get_year();
    this->month = date.get_month();
    this->day = date.get_day();
}

//DateTimeValue
DateTimeValue::DateTimeValue()
    : date(DateValue::now()), time(TimeValue::now())
{

}

DateTimeValue DateTimeValue::now()
{
    DateTimeValue value;

    value.date = DateValue::now();
    value.time = TimeValue::now();

    return value;
}

DateTimeValue DateTimeValue::zero()
{
    DateTimeValue value;

    value.date.set(0, 0, 0);
    value.time.set(0, 0);

    return value;
}

std::string DateTimeValue::toString()
{
    return date.toString() + " " + time.toString();
}

long DateTimeValue::getHashCode() const
{
    return date.getHashCode() * 10000 + time.getHashCode();
}

std::string DateTimeValue::getHashCodeText()
{
    return utils::numToString(getHashCode());
}
