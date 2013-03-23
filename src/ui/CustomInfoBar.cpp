/*
 * File:   CustomInfoBar.cpp
 * Author: piotr
 *
 * Created on July 2, 2012, 21:17 PM
 */

#include <gtkmm-3.0/gtkmm/widget.h>

#include "Resources.h"
#include "CustomInfoBar.h"

CustomInfoBar::CustomInfoBar(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::DrawingArea(cobject), refGlade(refGlade)
{
    this->messageType = Gtk::MESSAGE_INFO;
}

CustomInfoBar::CustomInfoBar()
{
}

CustomInfoBar::~CustomInfoBar()
{
}

void CustomInfoBar::on_realize()
{
    Gtk::Widget::on_realize();

    font.set_family(Resources::res->fontName);
    font.set_weight(Pango::WEIGHT_ULTRALIGHT);
}

bool CustomInfoBar::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();

    const int width = allocation.get_width();
    const int height = allocation.get_height();

    drawBackground(cr, width, height);
    drawText(cr, width, height);

    return true;
}

void CustomInfoBar::drawBackground(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    cr->set_antialias(Cairo::ANTIALIAS_NONE);

    Cairo::RefPtr<Cairo::LinearGradient> linearGradient = Cairo::LinearGradient::create(0, 0, 0, height);

    if (messageType == Gtk::MESSAGE_ERROR)
    {
        linearGradient->add_color_stop_rgb(0, 1.0, 0.4, 0.4);
        linearGradient->add_color_stop_rgb(1, 1.0, 0.3, 0.3);
    }

    if (messageType == Gtk::MESSAGE_INFO)
    {
        linearGradient->add_color_stop_rgb(0, 0.0, 0.75, 0.4);
        linearGradient->add_color_stop_rgb(1, 0.0, 0.65, 0.3);
    }

    cr->set_source(linearGradient);

    cr->rectangle(0, 0, width, height);
    cr->fill();

    cr->set_antialias(Cairo::ANTIALIAS_NONE);
    cr->set_line_width(1.0);

    if (messageType == Gtk::MESSAGE_ERROR)
        cr->set_source_rgb(1.0, 0.2, 0.2);

    if (messageType == Gtk::MESSAGE_INFO)
        cr->set_source_rgb(0.0, 0.5, 0.2);

    cr->rectangle(1, 1, width - 1, height - 1);
    cr->stroke();

    if (messageType == Gtk::MESSAGE_ERROR)
        cr->set_source_rgb(1.0, 0.4, 0.4);

    if (messageType == Gtk::MESSAGE_INFO)
        cr->set_source_rgb(0.0, 0.75, 0.4);

    cr->rectangle(2, 2, width - 3, height - 3);
    cr->stroke();
}

void CustomInfoBar::drawText(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height)
{
    font.set_size((height * 0.35) * PANGO_SCALE);

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);

    layout->set_text(text);
    layout->set_font_description(font);

    int text_width;
    int text_height;

    layout->get_pixel_size(text_width, text_height);

    const int textPosX = height * 0.2;
    const int textPosY = (height * 0.5) - (text_height * 0.5);

    cr->move_to(textPosX+1, textPosY+1);

    if (messageType == Gtk::MESSAGE_ERROR)
        cr->set_source_rgb(0.7, 0.0, 0.0);

    if (messageType == Gtk::MESSAGE_INFO)
        cr->set_source_rgb(0.0, 0.3, 0.0);

    layout->show_in_cairo_context(cr);

    cr->set_source_rgb(1.0, 1.0, 1.0);

    cr->move_to(textPosX, textPosY);
    layout->show_in_cairo_context(cr);
}

void CustomInfoBar::setText(Gtk::MessageType messageType, std::string text)
{
    this->messageType = messageType;
    this->text = text;

    this->queue_draw();
}
