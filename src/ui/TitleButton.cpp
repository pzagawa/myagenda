/*
 * File:   TitleButton.cpp
 * Author: piotr
 *
 * Created on June 25, 2012, 7:47 PM
 */

#include "Resources.h"
#include "TitleButton.h"

TitleButton::TitleButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Button(cobject), refGlade(refGlade)
{
   	l_red = 0.3;
	l_green = 0.3;
	l_blue = 0.3;

    r_red = 0.4;
	r_green = 0.4;
	r_blue = 0.4;
}

TitleButton::TitleButton()
{
}

TitleButton::~TitleButton()
{
}

void TitleButton::on_realize()
{
    Gtk::Widget::on_realize();

    fontDay.set_family(Resources::res->fontName);
    fontDay.set_weight(Pango::WEIGHT_ULTRALIGHT);

    this->set_label("");
}

void TitleButton::setText(std::string textLeft, std::string textRight)
{
    this->textLeft = textLeft;
    this->textRight = textRight;
    this->queue_draw();
}

bool TitleButton::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Button::on_draw(cr);

    Gtk::Allocation allocation = get_allocation();

    const int width = allocation.get_width();
    const int height = allocation.get_height();

    const int margin = 12;

    int textPosX;
    int textPosY;

    int text_width;
    int text_height;

    fontDay.set_size((height * 0.4) * PANGO_SCALE);

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);

    layout->set_font_description(fontDay);

    //draw text left
    layout->set_text(textLeft);
    layout->get_pixel_size(text_width, text_height);

    textPosX = margin;
    textPosY = (height * 0.5) - (text_height * 0.5);

    cr->move_to(textPosX, textPosY);
    cr->set_source_rgb(l_red, l_green, l_blue);
    layout->show_in_cairo_context(cr);

    //draw text right
    layout->set_text(textRight);
    layout->get_pixel_size(text_width, text_height);

    textPosX = width - margin - text_width;
    textPosY = (height * 0.5) - (text_height * 0.5);

    cr->move_to(textPosX, textPosY);
    cr->set_source_rgb(r_red, r_green, r_blue);
    layout->show_in_cairo_context(cr);

    return true;
}

void TitleButton::set_color_rgb_left(double red, double green, double blue)
{
    this->l_red = red;
    this->l_green = green;
    this->l_blue = blue;

    this->queue_draw();
}

void TitleButton::set_color_rgb_right(double red, double green, double blue)
{
    this->r_red = red;
    this->r_green = green;
    this->r_blue = blue;

    this->queue_draw();
}
