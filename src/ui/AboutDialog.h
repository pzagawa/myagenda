/*
 * File:   AboutDialog.h
 * Author: piotr
 *
 * Created on July 7, 2012, 20:36 PM
 */

#pragma once

#include <gtkmm.h>

class AboutDialog
	: public Gtk::AboutDialog
{
private:
	Glib::RefPtr<Gtk::Builder> ui;

public:
	AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~AboutDialog();

	static int create(Gtk::Window& parent);

private:
	virtual void on_realize();

};
