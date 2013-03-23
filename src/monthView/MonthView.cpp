/*
 * File:   MonthView.cpp
 * Author: piotr
 *
 * Created on June 22, 2012, 12:13 AM
 */

#include "MonthView.h"
#include <cairomm/cairomm.h>
#include <iostream>

namespace cal
{

MonthView::MonthView()
{
    selectedDate.clear();
   	isDaySelected = false;

    initializeDaysData();
}

MonthView::~MonthView()
{
}

void MonthView::initializeDaysData()
{
    int column = 0;
    int row = 0;

    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayData& dayData = daysData[index];

        column = index % DAYS_IN_WEEK;

        dayData.setPosition(column, row);

        if (column == (DAYS_IN_WEEK - 1))
            row++;
    }
}

void MonthView::initializeRectangles(int width, int height, int weekDaysHeight)
{
    const int rectWidth = width / DAYS_IN_WEEK;
    const int rectHeight = (height - weekDaysHeight) / WEEK_ROWS;
    const int horzOffset = (width - (rectWidth * DAYS_IN_WEEK)) * 0.5f;

    const int margin = 1;

    //initialize week days
    for (int index = 0; index < DAYS_IN_WEEK; index++)
    {
        MonthViewWeekDayRect& weekDayRect = weekDaysRect[index];

        int left = (index * rectWidth) + horzOffset;
        int top = weekDaysHeight + (index * rectHeight);

        weekDayRect.set(left + margin, margin, rectWidth - margin*2, weekDaysHeight - margin*2);
    }

    int columnIndex = 0;
    int rowIndex = 0;

    //initialize month days
    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayRect& dayRect = daysRect[index];
        MonthViewDayData& dayData = daysData[index];

        columnIndex = index % DAYS_IN_WEEK;

        dayRect.setData(&dayData);

        int left = (columnIndex * rectWidth) + horzOffset;
        int top = weekDaysHeight + (rowIndex * rectHeight);

        dayRect.set(left + margin, top + margin, rectWidth - margin*2, rectHeight - margin*2);

        if (columnIndex == 6)
            rowIndex++;
    }
}

void MonthView::setViewDate(Glib::Date date)
{
    baseDate = date;
    todayDate.set_time_current();

    queryForDaySummaryInfo();
    updateDaysData();
}

void MonthView::setSelectedDate(Glib::Date date)
{
    selectedDate = date;
    isDaySelected = true;

    updateDaysData();

    MonthViewDayData* data = getDayData(selectedDate);
    signal_day_selected.emit(data);
}

void MonthView::setViewAndSelectDate(Glib::Date date)
{
    baseDate = date;
    todayDate.set_time_current();

    selectedDate = date;
    isDaySelected = true;

    queryForDaySummaryInfo();
    updateDaysData();

    MonthViewDayData* data = getDayData(selectedDate);
    signal_day_selected.emit(data);
}

void MonthView::clearSelectedDate()
{
    selectedDate.clear();
   	isDaySelected = false;
    updateDaysData();
}

Glib::Date MonthView::getViewBeginDate()
{
    Glib::Date date = baseDate;

    //align date to first day of month
    date.set_day(1);

    //search for week start day
    while (date.get_weekday() != Glib::Date::MONDAY)
        date.subtract_days(1);

    return date;
}

Glib::Date MonthView::getViewEndDate()
{
    Glib::Date date = getViewBeginDate();

    date.add_days(TOTAL_DAYS - 1);

    return date;
}

void MonthView::queryForDaySummaryInfo()
{
    Glib::Date date = getViewBeginDate();
    Glib::Date dateEnd = getViewEndDate();

    signal_query_for_data.emit(date, dateEnd, summaryMap);
}

void MonthView::updateDaysData()
{
    Glib::Date date = getViewBeginDate();

    //initialize month days
    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayData& dayData = daysData[index];

        dayData.setDate(date);

        dayData.setCurrentMonth(isCurrentMonth(date));
        dayData.setToday(isToday(date));
        dayData.setSelected(isSelectedDate(date));

        //get day summary info
        const long dateKey = dayData.getDateValue().getHashCode();
        NoteInfoSummary& daySummary = summaryMap[dateKey];
        dayData.setInfoSummary(daySummary);

        date.add_days(1);
    }

    //initialize week days (based on calculated days dates)
    for (int index = 0; index < DAYS_IN_WEEK; index++)
    {
        MonthViewWeekDayRect& weekDayRect = weekDaysRect[index];
        MonthViewDayData& dayData = daysData[index];
        weekDayRect.setText(dayData.getWeekDayText());
    }

    //redraw view
    this->queue_draw();
}

bool MonthView::isCurrentMonth(Glib::Date& date)
{
    return (baseDate.get_month() == date.get_month());
}

bool MonthView::isToday(Glib::Date& date)
{
    if (todayDate.get_day() == date.get_day())
        if (todayDate.get_month() == date.get_month())
            if (todayDate.get_year() == date.get_year())
                return true;

    return false;
}

bool MonthView::isSelectedDate(Glib::Date& date)
{
    if (isDaySelected)
    {
        if (selectedDate.get_day() == date.get_day())
            if (selectedDate.get_month() == date.get_month())
                if (selectedDate.get_year() == date.get_year())
                    return true;
    }

    return false;
}

bool MonthView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();

    const int width = allocation.get_width();
    const int height = allocation.get_height();

    const int weekDaysHeight = 22;

    initializeRectangles(width, height, weekDaysHeight);

    //draw week days rectangles
    for (int index = 0; index < DAYS_IN_WEEK; index++)
    {
        MonthViewWeekDayRect& weekDayRect = weekDaysRect[index];
        cr->save();
        weekDayRect.draw(cr);
        cr->restore();
    }

    //draw month days rectangles
    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayRect& dayRect = daysRect[index];

        cr->save();
        dayRect.draw(cr);
        cr->restore();
    }

    return true;
}

std::string MonthView::getCurrentMonthDateText()
{
    Glib::ustring s(baseDate.format_string("%B %Y"));
    return s.lowercase();
}

std::string MonthView::getCurrentMonthNameText()
{
    Glib::ustring s(baseDate.format_string("%B"));
    return s.lowercase();
}

std::string MonthView::getCurrentMonthYearText()
{
    Glib::ustring s(baseDate.format_string("%Y"));
    return s.lowercase();
}

Glib::Date MonthView::getSelectedDate()
{
    return selectedDate;
}

std::string MonthView::getSelectedDateText()
{
    Glib::ustring s(selectedDate.format_string("%A, %d-%m-%Y"));
    return s.lowercase();
}

MonthViewDayData* MonthView::getDayData(int x, int y)
{
    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayRect& dayRect = daysRect[index];
        MonthViewDayData& dayData = daysData[index];

        if (dayRect.isInside(x, y))
            return &dayData;
    }

    return NULL;
}

MonthViewDayData* MonthView::getDayData(Glib::Date& date)
{
    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayData& dayData = daysData[index];
        if (dayData.getDate() == date)
            return &dayData;
    }

    return NULL;
}

void MonthView::clearSelection()
{
    for (int index = 0; index < TOTAL_DAYS; index++)
    {
        MonthViewDayData& dayData = daysData[index];
        dayData.setSelected(false);
    }
}

void MonthView::triggerDaySelectionEvent()
{
    MonthViewDayData* data = getDayData(selectedDate);
    signal_day_selected.emit(data);
}

void MonthView::triggerMonthSelectionEvent()
{
    queryForDaySummaryInfo();
    updateDaysData();
}

//calendar namespace
};
