/*
 * File:   Exception.h
 * Author: piotr
 *
 * Created on July 1, 2012, 3:19 PM
 */

#pragma once

#include <gtkmm.h>

class Exception
{
private:
	Glib::ustring message;

public:
	Exception(Glib::ustring message);
	Exception(const Exception& orig);
	virtual ~Exception();

public:
	Glib::ustring getMessage();

};
