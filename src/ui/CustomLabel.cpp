/*
 * File:   CustomLabel.cpp
 * Author: piotr
 *
 * Created on July 1, 2012, 13:09 PM
 */

#include "Resources.h"
#include "CustomLabel.h"

CustomLabel::CustomLabel(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Label(cobject), refGlade(refGlade)
{
   	red = 0.5;
	green = 0.25;
	blue = 0.0;
}

CustomLabel::CustomLabel()
{
}

CustomLabel::~CustomLabel()
{
}

void CustomLabel::on_realize()
{
    Gtk::Widget::on_realize();

}

bool CustomLabel::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();

    const int width = allocation.get_width();
    const int height = allocation.get_height();

    Glib::RefPtr<Pango::Layout> layout = this->get_layout();

    cr->set_source_rgb(red, green, blue);

    layout->show_in_cairo_context(cr);

    return true;
}

void CustomLabel::set_color_rgb(double red, double green, double blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;

    this->queue_draw();
}
