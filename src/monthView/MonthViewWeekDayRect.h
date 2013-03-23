/*
 * File:   MonthViewWeekDayRect.h
 * Author: piotr
 *
 * Created on June 22, 2012, 11:01 PM
 */

#pragma once

#include <cairomm/context.h>
#include <pangomm.h>

namespace cal
{

class MonthViewWeekDayRect
{
private:
	int x;
	int y;
	int width;
	int height;
	std::string text;

    Pango::FontDescription fontDay;

public:
	MonthViewWeekDayRect();
	MonthViewWeekDayRect(const MonthViewWeekDayRect& orig);
	virtual ~MonthViewWeekDayRect();

private:
	void initialize();
	void drawText(const Cairo::RefPtr<Cairo::Context>& cr);

public:
	void setText(std::string text);
	void set(int x, int y, int width, int height);
	void draw(const Cairo::RefPtr<Cairo::Context>& cr);

};

//calendar namespace
};
