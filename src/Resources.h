/*
 * File:   Resources.h
 * Author: piotr
 *
 * Created on June 26, 2012, 10:20 PM
 */

#pragma once

#include <gtkmm.h>
#include <string>

class Resources
{
private:
	Glib::RefPtr<Gtk::Builder> ui;

public:
	static Resources* res;

public:
	std::string app_name;
	std::string app_author;
	std::string app_version;

public:
	Gtk::Image* imgReminderIcon;
	Gtk::Image* imgReminderOnIcon;
	Gtk::Image* imgBtnEdit;
	Gtk::Image* imgBtnDelete;
	Gtk::Image* imgBtnAbout;
	Gtk::Image* imgBtnNewNote;

public:
	std::string fontName;

public:
	Resources(Glib::RefPtr<Gtk::Builder> ui);
	virtual ~Resources();

public:
	void initialize();

};
