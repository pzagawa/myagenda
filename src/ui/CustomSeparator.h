/*
 * File:   CustomSeparator.h
 * Author: piotr
 *
 * Created on July 11, 2012, 6:09 PM
 */

#pragma once

#include <gtkmm.h>

class CustomSeparator
	: public Gtk::DrawingArea
{
public:
	enum Type
	{
		SOLID,
		BOTTOM_SHADOW,
	};

private:
	Glib::RefPtr<Gtk::Builder> refGlade;
	Type viewType;

public:
	CustomSeparator(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~CustomSeparator();

protected:
	virtual void on_realize();
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

public:
	void setType(Type type);

};
