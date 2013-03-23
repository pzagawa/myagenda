/*
 * File:   Preferences.h
 * Author: piotr
 *
 * Created on July 10, 2012, 6:54 PM
 */

#pragma once

class Preferences
{
public:
	static Preferences* prefs;

public:
	Preferences();
	Preferences(const Preferences& orig);
	virtual ~Preferences();

public:
	int getNewNoteMinutes();
	int getNotificationExpirationMinutes();

};
