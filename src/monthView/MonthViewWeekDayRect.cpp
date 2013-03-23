/*
 * File:   MonthViewWeekDayRect.cpp
 * Author: piotr
 *
 * Created on June 22, 2012, 11:01 PM
 */

#include "MonthViewWeekDayRect.h"
#include "Resources.h"
#include <cairomm/enums.h>
#include <iostream>

namespace cal
{

MonthViewWeekDayRect::MonthViewWeekDayRect()
{
    initialize();
}

MonthViewWeekDayRect::MonthViewWeekDayRect(const MonthViewWeekDayRect& orig)
{
}

MonthViewWeekDayRect::~MonthViewWeekDayRect()
{
}

void MonthViewWeekDayRect::initialize()
{
    fontDay.set_family(Resources::res->fontName);
    fontDay.set_weight(Pango::WEIGHT_ULTRALIGHT);
}

void MonthViewWeekDayRect::setText(std::string text)
{
    this->text = text;
}

void MonthViewWeekDayRect::set(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void MonthViewWeekDayRect::draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    drawText(cr);
}

void MonthViewWeekDayRect::drawText(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    fontDay.set_absolute_size(14 * PANGO_SCALE);

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);

    layout->set_text(text);
    layout->set_font_description(fontDay);

    int text_width;
    int text_height;

    layout->get_pixel_size(text_width, text_height);

    const int baseLine = layout->get_baseline() / PANGO_SCALE;

    const int marginY = height * 0.2;

    const int textPosX = x + (width * 0.5) - (text_width * 0.5);
    const int textPosY = y + (height - baseLine) - marginY;

    cr->move_to(textPosX, textPosY);

    cr->set_source_rgb(0.3, 0.3, 0.3);

    layout->show_in_cairo_context(cr);
}

//calendar namespace
};
