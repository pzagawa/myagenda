/*
 * File:   TitleButton.h
 * Author: piotr
 *
 * Created on June 25, 2012, 7:47 PM
 */

#pragma once

#include <gtkmm.h>

class TitleButton
	: public Gtk::Button
{
private:
	Glib::RefPtr<Gtk::Builder> refGlade;
    Pango::FontDescription fontDay;
	std::string textLeft;
	std::string textRight;

	double l_red;
	double l_green;
	double l_blue;

	double r_red;
	double r_green;
	double r_blue;

public:
	TitleButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	TitleButton();
	virtual ~TitleButton();

public:
	void setText(std::string textLeft, std::string textRight);
	void set_color_rgb_left(double red, double green, double blue);
	void set_color_rgb_right(double red, double green, double blue);

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual void on_realize();

};
