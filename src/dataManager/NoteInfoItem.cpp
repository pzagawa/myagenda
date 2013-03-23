/*
 * File:   NoteItemData.cpp
 * Author: piotr
 *
 * Created on June 26, 2012, 8:54 PM
 */

#include "NoteInfoItem.h"
#include <cstdio>

NoteInfoItem::NoteInfoItem()
{
    uid = 0;
    _isReminder = false;
    _isNotificationCleared = false;
}

NoteInfoItem::NoteInfoItem(const NoteInfoItem& orig)
{
	this->uid = orig.uid;
	this->date = orig.date;
	this->time = orig.time;
	this->_isReminder = orig._isReminder;
    this->_isNotificationCleared = orig._isNotificationCleared;
}

NoteInfoItem& NoteInfoItem::operator=(NoteInfoItem& orig)
{
	this->uid = orig.uid;
	this->date = orig.date;
	this->time = orig.time;
	this->_isReminder = orig._isReminder;
    this->_isNotificationCleared = orig._isNotificationCleared;

    return *this;
}

NoteInfoItem::~NoteInfoItem()
{
}

void NoteInfoItem::reset()
{
	this->uid = 0;
	this->date.set(0, 0, 0);
	this->time.set(0, 0);
	this->_isReminder = false;
    this->_isNotificationCleared = false;
}

std::string NoteInfoItem::toString()
{
    std::string s;

    char buff[16];

    sprintf(buff, "%4ld", uid);

    s += buff;
    s += ". ";

    s += date.toString();
    s += " ";

    s += time.toString();
    s += ". ";

    if (_isReminder)
        s += "reminder. ";

    if (_isNotificationCleared)
        s += "cleared. ";

    return s;
}

long NoteInfoItem::getUid()
{
    return uid;
}

long NoteInfoItem::getDate()
{
    return date.getHashCode();
}

long NoteInfoItem::getTime()
{
    return time.getHashCode();
}

bool NoteInfoItem::isReminder()
{
    return _isReminder;
}

bool NoteInfoItem::isNotificationCleared()
{
    return _isNotificationCleared;
}

void NoteInfoItem::parseRecord(sql::Record& record)
{
    reset();

    this->uid = record.getKeyIdValue()->asInteger();

    this->date = record.getValue("date")->asInteger();
    this->time = record.getValue("time")->asInteger();

    this->_isReminder = record.getValue("isReminder")->asBool();

    if (record.getValue("isNotificationCleared")->asBool())
        this->_isNotificationCleared = true;
}

long NoteInfoItem::getDateTime() const
{
    return date.getHashCode() * 10000 + time.getHashCode();
}
