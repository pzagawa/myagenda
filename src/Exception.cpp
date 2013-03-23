/*
 * File:   Exception.cpp
 * Author: piotr
 *
 * Created on July 1, 2012, 3:19 PM
 */

#include "Exception.h"

Exception::Exception(Glib::ustring message)
    : message(message)
{
}

Exception::Exception(const Exception& orig)
{
    this->message = orig.message;
}

Exception::~Exception()
{
}

Glib::ustring Exception::getMessage()
{
    return message;
}
