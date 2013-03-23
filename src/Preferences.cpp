/*
 * File:   Preferences.cpp
 * Author: piotr
 *
 * Created on July 10, 2012, 6:54 PM
 */

#include "Preferences.h"
#include <cstdlib>

Preferences* Preferences::prefs = NULL;

Preferences::Preferences()
{
    prefs = this;
}

Preferences::Preferences(const Preferences& orig)
{
}

Preferences::~Preferences()
{
}

//How many minutes to add to current time, when creating new note
int Preferences::getNewNoteMinutes()
{
    return 15;
}

//How many minutes wait before show again the same notification
int Preferences::getNotificationExpirationMinutes()
{
    return 5;
}
