/*
 * File:   NoteInfoSummary.h
 * Author: piotr
 *
 * Created on July 5, 2012, 0:55 AM
 */

#pragma once

#include <string>
#include "NoteInfoItem.h"

class NoteInfoSummary
{
private:
	int notesCount;
	int notificationsCount;

public:
	NoteInfoSummary();
	NoteInfoSummary(const NoteInfoSummary& orig);
	virtual ~NoteInfoSummary();
	NoteInfoSummary& operator=(NoteInfoSummary& other);
	std::string toString();

public:
	long getNotesCount();
	long getNotificationsCount();

public:
	void aggregate(NoteInfoItem& item, long timeNow);

};
