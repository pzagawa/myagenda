/*
 * File:   CustomLabel.h
 * Author: piotr
 *
 * Created on July 1, 2012, 13:09 PM
 */

#pragma once

#include <gtkmm.h>

class CustomLabel
	: public Gtk::Label
{
private:
	Glib::RefPtr<Gtk::Builder> refGlade;
	double red;
	double green;
	double blue;

public:
	CustomLabel(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	CustomLabel();
	virtual ~CustomLabel();

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual void on_realize();

public:
	void set_color_rgb(double red, double green, double blue);

};
