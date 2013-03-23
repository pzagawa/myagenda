/*
 * File:   NoteItemData.cpp
 * Author: piotr
 *
 * Created on July 5, 2012, 0:55 AM
 */

#include "NoteInfoSummary.h"
#include <cstdio>

NoteInfoSummary::NoteInfoSummary()
{
	notesCount = 0;
	notificationsCount = 0;
}

NoteInfoSummary::NoteInfoSummary(const NoteInfoSummary& orig)
{
	this->notesCount = orig.notesCount;
	this->notificationsCount = orig.notificationsCount;
}

NoteInfoSummary::~NoteInfoSummary()
{
}

NoteInfoSummary& NoteInfoSummary::operator=(NoteInfoSummary& other)
{
	this->notesCount = other.notesCount;
	this->notificationsCount = other.notificationsCount;

    return *this;
}

std::string NoteInfoSummary::toString()
{
    char buff[32];
    sprintf(buff, "%d/%d", notificationsCount, notesCount);
    return buff;
}

long NoteInfoSummary::getNotesCount()
{
    return this->notesCount;
}

long NoteInfoSummary::getNotificationsCount()
{
    return this->notificationsCount;
}

void NoteInfoSummary::aggregate(NoteInfoItem& item, long timeNow)
{
	this->notesCount++;

    if (item.isReminder())
    {
        if (!item.isNotificationCleared())
        {
            if (timeNow >= item.getDateTime())
            {
                this->notificationsCount++;
            }
        }
    }
}
