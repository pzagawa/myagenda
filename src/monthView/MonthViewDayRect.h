/*
 * File:   MonthViewDayRect.h
 * Author: piotr
 *
 * Created on June 22, 2012, 11:01 PM
 */

#pragma once

#include <cairomm/context.h>
#include <pangomm.h>
#include "MonthViewDayData.h"

namespace cal
{

class MonthViewDayRect
{
private:
	int x;
	int y;
	int width;
	int height;

	MonthViewDayData* data;
    Pango::FontDescription fontDay;

public:
	MonthViewDayRect();
	MonthViewDayRect(const MonthViewDayRect& orig);
	virtual ~MonthViewDayRect();

private:
	void initialize();
	void drawBackground(const Cairo::RefPtr<Cairo::Context>& cr);
	void drawSelectionBackground(const Cairo::RefPtr<Cairo::Context>& cr);
	void drawInnerShadow(const Cairo::RefPtr<Cairo::Context>& cr);
	void drawText(const Cairo::RefPtr<Cairo::Context>& cr);
	void drawTodayMark(const Cairo::RefPtr<Cairo::Context>& cr);
	void drawInfoSummary(const Cairo::RefPtr<Cairo::Context>& cr);

public:
	void setData(MonthViewDayData* data);
	void set(int x, int y, int width, int height);
	void draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool isInside(int x, int y);

};

//calendar namespace
};
