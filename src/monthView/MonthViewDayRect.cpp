/*
 * File:   MonthViewDayRect.cpp
 * Author: piotr
 *
 * Created on June 22, 2012, 11:01 PM
 */

#include "MonthViewDayRect.h"
#include "Resources.h"
#include <cairomm/enums.h>
#include <iostream>

namespace cal
{

MonthViewDayRect::MonthViewDayRect()
    : data(NULL)
{
    initialize();
}

MonthViewDayRect::MonthViewDayRect(const MonthViewDayRect& orig)
{
}

MonthViewDayRect::~MonthViewDayRect()
{
}

void MonthViewDayRect::initialize()
{
    fontDay.set_family(Resources::res->fontName);
    fontDay.set_weight(Pango::WEIGHT_NORMAL);
}

void MonthViewDayRect::setData(MonthViewDayData* data)
{
    this->data = data;
}

void MonthViewDayRect::set(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void MonthViewDayRect::draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    if (data->isSelected())
    {
        drawSelectionBackground(cr);
    }
    else
    {
        drawBackground(cr);
    }

    drawInfoSummary(cr);

    if (data->isToday())
        drawTodayMark(cr);

    if (data->isSelected())
        drawInnerShadow(cr);

    drawText(cr);
}

void MonthViewDayRect::drawBackground(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    if (data->isCurrentMonth())
    {
        Cairo::RefPtr<Cairo::LinearGradient> linearGradient = Cairo::LinearGradient::create(x, y, x, y + height);
        linearGradient->add_color_stop_rgb(0, 0.85, 0.85, 0.85);
        linearGradient->add_color_stop_rgb(1, 0.75, 0.75, 0.75);
        cr->set_source(linearGradient);
    }
    else
    {
        cr->set_source_rgb(0.90, 0.90, 0.90);
    }

    cr->rectangle(x, y, width, height);
    cr->fill();
}

void MonthViewDayRect::drawSelectionBackground(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    if (data->isCurrentMonth())
    {
        Cairo::RefPtr<Cairo::LinearGradient> linearGradient = Cairo::LinearGradient::create(x, y, x, y + height);
        linearGradient->add_color_stop_rgb(0, 0.10, 0.60, 0.90);
        linearGradient->add_color_stop_rgb(1, 0.20, 0.80, 1.00);
        cr->set_source(linearGradient);
    }
    else
    {
        if (data->isSelected())
        {
            cr->set_source_rgb(0.85, 0.85, 0.85);
        }
        else
        {
            cr->set_source_rgb(0.90, 0.90, 0.90);
        }
    }

    cr->rectangle(x, y, width, height);
    cr->fill();
}

void MonthViewDayRect::drawTodayMark(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);
    cr->set_line_width(1);

    int markHeight = height * 0.25;
    int markWidth = width * 0.15;
    int markHalfHeight = markHeight * 0.5;

    int top = y + height - markHeight;
    int left = x + 0.5;

    if (data->isCurrentMonth() && !data->isSelected())
    {
        //draw highliht
        top += 1;
        left += 1;

        if (data->isSelected())
        {
            cr->set_source_rgb(0.70, 0.80, 0.90);
        }
        else
        {
            cr->set_source_rgb(0.92, 0.92, 0.92);
        }

        cr->move_to(left, top - markHalfHeight);
        cr->line_to(left + markWidth, top);
        cr->line_to(left, top + markHalfHeight);
        cr->close_path();
        cr->fill();

        top -= 1;
        left -= 1;
    }

    //fill dark
    if (data->isCurrentMonth())
    {
        if (data->isSelected())
        {
            cr->set_source_rgb(0.15, 0.15, 0.40);
        }
        else
        {
            cr->set_source_rgb(0.2, 0.2, 0.2);
        }
    }
    else
    {
        cr->set_source_rgb(0.6, 0.6, 0.6);
    }

    cr->move_to(left, top - markHalfHeight);
    cr->line_to(left + markWidth, top);
    cr->line_to(left, top + markHalfHeight);
    cr->close_path();
    cr->fill();
}

void MonthViewDayRect::drawInnerShadow(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    const int SIZE = height * 0.1;
    const double ALPHA = data->isCurrentMonth() ? 0.3 : 0.2;

    Cairo::RefPtr<Cairo::LinearGradient> linearGradientTop = Cairo::LinearGradient::create(x, y, x, y + SIZE);
    linearGradientTop->add_color_stop_rgba(0, 0.00, 0.00, 0.00, ALPHA);
    linearGradientTop->add_color_stop_rgba(1, 0.00, 0.00, 0.00, 0.0);
    cr->set_source(linearGradientTop);
    cr->rectangle(x, y, width, height);
    cr->fill();

    Cairo::RefPtr<Cairo::LinearGradient> linearGradientBottom = Cairo::LinearGradient::create(x, y + height - SIZE, x, y + height);
    linearGradientBottom->add_color_stop_rgba(0, 0.00, 0.00, 0.00, 0.0);
    linearGradientBottom->add_color_stop_rgba(1, 0.00, 0.00, 0.00, ALPHA);
    cr->set_source(linearGradientBottom);
    cr->rectangle(x, y, width, height);
    cr->fill();

    Cairo::RefPtr<Cairo::LinearGradient> linearGradientLeft = Cairo::LinearGradient::create(x, y, x + SIZE, y);
    linearGradientLeft->add_color_stop_rgba(0, 0.00, 0.00, 0.00, ALPHA);
    linearGradientLeft->add_color_stop_rgba(1, 0.00, 0.00, 0.00, 0.0);
    cr->set_source(linearGradientLeft);
    cr->rectangle(x, y, width, height);
    cr->fill();

    Cairo::RefPtr<Cairo::LinearGradient> linearGradientRight = Cairo::LinearGradient::create(x + width - SIZE, y, x + width, y);
    linearGradientRight->add_color_stop_rgba(0, 0.00, 0.00, 0.00, 0.0);
    linearGradientRight->add_color_stop_rgba(1, 0.00, 0.00, 0.00, ALPHA);
    cr->set_source(linearGradientRight);
    cr->rectangle(x, y, width, height);
    cr->fill();
}

void MonthViewDayRect::drawText(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    fontDay.set_absolute_size((width * PANGO_SCALE) * 0.5);

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);

    layout->set_text(data->getDayText());
    layout->set_font_description(fontDay);

    int text_width;
    int text_height;

    layout->get_pixel_size(text_width, text_height);

    const int baseLine = layout->get_baseline() / PANGO_SCALE;

    const int marginX = width * 0.08;
    const int marginY = height * 0.11;

    const int textPosX = x + (width - text_width) - marginX;
    const int textPosY = y + (height - baseLine) - marginY;

    cr->move_to(textPosX, textPosY);

    if (data->isCurrentMonth())
    {
        const int highlightSize = 1;

        //draw highlight
        if (data->isSelected())
        {
            cr->set_source_rgb(0.70, 0.80, 0.90);
        }
        else
        {
            cr->set_source_rgb(0.92, 0.92, 0.92);
        }

        layout->show_in_cairo_context(cr);
        cr->move_to(textPosX - highlightSize, textPosY - highlightSize);

        if (data->isSelected())
        {
            cr->set_source_rgb(0.15, 0.15, 0.40);
        }
        else
        {
            cr->set_source_rgb(0.2, 0.2, 0.2);
        }
    }
    else
    {
        cr->set_source_rgb(0.6, 0.6, 0.6);
    }

    layout->show_in_cairo_context(cr);
}

void MonthViewDayRect::drawInfoSummary(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->save();
    cr->set_antialias(Cairo::ANTIALIAS_DEFAULT);

    NoteInfoSummary& info = data->getInfoSummary();

    const int marginX = 10;
    const int marginY = 10;

    const bool isReminder = (info.getNotificationsCount() > 0);

    if (info.getNotesCount() > 0)
    {
        const int size = 3;

        const int left = x + marginX;
        const int top = y + marginY;

        cr->arc(left, top, size, 0, 2*M_PI);

        if (data->isCurrentMonth())
        {
            if (data->isSelected())
            {
                if (isReminder)
                {
                    cr->set_source_rgb(0.2, 0.1, 0.0);
                    cr->stroke_preserve();
                    cr->set_source_rgb(1.0, 0.5, 0.0);
                }
                else
                {
                    cr->set_source_rgb(0.15, 0.15, 0.40);
                    cr->stroke_preserve();
                    cr->set_source_rgb(0.15, 0.15, 0.40);
                }
            }
            else
            {
                if (isReminder)
                {
                    cr->set_source_rgb(0.4, 0.2, 0.0);
                    cr->stroke_preserve();
                    cr->set_source_rgb(1.0, 0.5, 0.0);
                }
                else
                {
                    cr->set_source_rgb(0.4, 0.4, 0.4);
                    cr->stroke_preserve();
                    cr->set_source_rgb(0.4, 0.4, 0.4);
                }
            }
        }
        else
        {
            cr->set_source_rgb(0.6, 0.6, 0.6);
            cr->stroke_preserve();
            cr->set_source_rgb(0.6, 0.6, 0.6);
        }

        cr->fill();
    }

    cr->restore();
}

bool MonthViewDayRect::isInside(int x, int y)
{
    const int right = this->x + width;
    const int bottom = this->y + height;

    if (x > this->x && x < right)
        if (y > this->y && y < bottom)
            return true;

    return false;
}

//calendar namespace
};
