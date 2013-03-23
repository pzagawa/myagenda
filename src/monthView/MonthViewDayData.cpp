/*
 * File:   MonthViewDayData.cpp
 * Author: piotr
 *
 * Created on June 23, 2012, 4:28 PM
 */

#include <glibmm/ustring.h>
#include "MonthViewDayData.h"
#include "DateTimeValue.h"

namespace cal
{

MonthViewDayData::MonthViewDayData()
{
}

MonthViewDayData::~MonthViewDayData()
{
}

void MonthViewDayData::setPosition(int column, int row)
{
    this->column = column;
    this->row = row;
}

int MonthViewDayData::getDateAsKey()
{
    return (date.get_year() * 10000) + (date.get_month() * 100) + date.get_day();
}

bool MonthViewDayData::equals(MonthViewDayData& data)
{
    return data.getDateAsKey() == this->getDateAsKey();
}

void MonthViewDayData::setDate(Glib::Date& date)
{
    this->date = date;
}

Glib::Date MonthViewDayData::getDate()
{
    return date;
}

DateValue MonthViewDayData::getDateValue()
{
    return date;
}

void MonthViewDayData::setCurrentMonth(bool value)
{
    _isCurrentMonth = value;
}

void MonthViewDayData::setToday(bool value)
{
    _isToday = value;
}

void MonthViewDayData::setSelected(bool value)
{
    _isSelected = value;
}

void MonthViewDayData::setInfoSummary(NoteInfoSummary& value)
{
    infoSummary = value;
}

bool MonthViewDayData::isCurrentMonth()
{
    return _isCurrentMonth;
}

bool MonthViewDayData::isToday()
{
    return _isToday;
}

bool MonthViewDayData::isSelected()
{
    return _isSelected;
}

NoteInfoSummary& MonthViewDayData::getInfoSummary()
{
    return infoSummary;
}

std::string MonthViewDayData::getDayText()
{
    return date.format_string("%e");
}

std::string MonthViewDayData::getWeekDayText()
{
    Glib::ustring s(date.format_string("%a"));
    return s.lowercase();
}

std::string MonthViewDayData::toString()
{
    std::string s = date.format_string("%a, %d-%m-%Y, ");

    s += (isCurrentMonth() ? "cm, " : "");
    s += (isToday() ? "today, " : "");
    s += (isSelected() ? "selected, " : "");

    return s;
}

//calendar namespace
};
