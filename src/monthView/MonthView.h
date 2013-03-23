/*
 * File:   MonthView.h
 * Author: piotr
 *
 * Created on June 22, 2012, 12:13 AM
 */

#pragma once

#include <gtkmm.h>
#include "DataTypes.h"
#include "MonthViewDayRect.h"
#include "MonthViewDayData.h"
#include "MonthViewWeekDayRect.h"

namespace cal
{

class MonthView
	: public Gtk::DrawingArea
{
public:
	const static int DAYS_IN_WEEK = 7;
	const static int WEEK_ROWS = 6;
	const static int WEEK_ROWS_WITHOUT_LAST = 5;
	const static int TOTAL_DAYS = DAYS_IN_WEEK * WEEK_ROWS;

private:
	bool isDaySelected;

	Glib::Date baseDate;
	Glib::Date todayDate;
	Glib::Date selectedDate;

	MonthViewDayRect daysRect[TOTAL_DAYS];
	MonthViewDayData daysData[TOTAL_DAYS];
	MonthViewWeekDayRect weekDaysRect[DAYS_IN_WEEK];

	//summary info for each day of view
	data::NoteInfoSummaryMap summaryMap;

public:
	sigc::signal<void, MonthViewDayData*> signal_day_selected;
	sigc::signal<void, Glib::Date, Glib::Date, data::NoteInfoSummaryMap&> signal_query_for_data;

public:
	MonthView();
	virtual ~MonthView();

private:
	void initializeDaysData();
	void initializeRectangles(int width, int height, int weekDaysHeight);
	void initializeDayFont();
	void updateDaysData();
	Glib::Date getViewBeginDate();
	Glib::Date getViewEndDate();
	bool isCurrentMonth(Glib::Date& date);
	bool isToday(Glib::Date& date);
	bool isSelectedDate(Glib::Date& date);
	void clearSelectedDate();
	void clearSelection();
	void queryForDaySummaryInfo();

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

public:
	void setViewDate(Glib::Date date);
	void setSelectedDate(Glib::Date date);
	void setViewAndSelectDate(Glib::Date date);
	void triggerDaySelectionEvent();
	void triggerMonthSelectionEvent();

public:
	Glib::Date getSelectedDate();
	std::string getSelectedDateText();
	std::string getCurrentMonthDateText();
	std::string getCurrentMonthNameText();
	std::string getCurrentMonthYearText();
	MonthViewDayData* getDayData(int x, int y);
	MonthViewDayData* getDayData(Glib::Date& date);

};

//calendar namespace
};
