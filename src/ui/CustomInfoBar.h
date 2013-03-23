/*
 * File:   CustomInfoBar.h
 * Author: piotr
 *
 * Created on July 2, 2012, 21:17 PM
 */

#pragma once

#include <gtkmm.h>

class CustomInfoBar
	: public Gtk::DrawingArea
{
private:
	Glib::RefPtr<Gtk::Builder> refGlade;
    Pango::FontDescription font;
	Gtk::MessageType messageType;
	std::string text;

public:
	CustomInfoBar(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	CustomInfoBar();
	virtual ~CustomInfoBar();

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual void on_realize();

private:
	void drawBackground(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawText(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);

public:
	void setText(Gtk::MessageType messageType, std::string text);

};
