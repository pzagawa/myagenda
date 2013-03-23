/*
 * File:   MonthViewDayData.h
 * Author: piotr
 *
 * Created on June 23, 2012, 4:28 PM
 */

#pragma once

#include <glibmm/date.h>
#include "DateTimeValue.h"
#include "NoteInfoSummary.h"

namespace cal
{

class MonthViewDayData
{
private:
	Glib::Date date;

	int column;
	int row;

	bool _isCurrentMonth;
	bool _isToday;
	bool _isSelected;

	NoteInfoSummary infoSummary;

public:
	MonthViewDayData();
	virtual ~MonthViewDayData();

public:
	void setPosition(int column, int row);
	void setDate(Glib::Date& date);
	void setCurrentMonth(bool value);
	void setToday(bool value);
	void setSelected(bool value);
	void setInfoSummary(NoteInfoSummary& value);

public:
	bool equals(MonthViewDayData& data);
	Glib::Date getDate();
	DateValue getDateValue();
	int getDateAsKey();
	bool isCurrentMonth();
	bool isToday();
	bool isSelected();
	NoteInfoSummary& getInfoSummary();
	std::string toString();
	std::string getDayText();
	std::string getWeekDayText();

};

//calendar namespace
};
