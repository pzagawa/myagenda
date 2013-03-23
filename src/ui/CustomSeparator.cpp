/*
 * File:   CustomSeparator.h
 * Author: piotr
 *
 * Created on July 11, 2012, 6:09 PM
 */

#include "CustomSeparator.h"

CustomSeparator::CustomSeparator(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::DrawingArea(cobject), refGlade(refGlade)
{
    this->viewType = SOLID;
}

CustomSeparator::~CustomSeparator()
{
}

void CustomSeparator::on_realize()
{
    Gtk::Widget::on_realize();

}

void CustomSeparator::setType(Type type)
{
    this->viewType = type;
}

bool CustomSeparator::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();

    int width = allocation.get_width();
    int height = allocation.get_height();

    if (viewType == SOLID)
    {
        cr->set_source_rgb(0.8, 0.8, 0.8);
        cr->paint();
    }

    if (viewType == BOTTOM_SHADOW)
    {
        Cairo::RefPtr<Cairo::LinearGradient> linearGradient = Cairo::LinearGradient::create(0, 0, 0, height);
        linearGradient->add_color_stop_rgba(0, 0.00, 0.00, 0.00, 0.1);
        linearGradient->add_color_stop_rgba(1, 0.00, 0.00, 0.00, 0.0);

        cr->set_source(linearGradient);
        cr->rectangle(0, 0, width, height);
        cr->fill();
    }

    return true;
}
