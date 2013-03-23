/*
 * File:   NoteItemData.cpp
 * Author: piotr
 *
 * Created on June 26, 2012, 8:54 PM
 */

#include "NoteItemData.h"
#include <cstdio>

namespace note
{

ItemData::ItemData()
{
    uid = 0;
    _isReminder = false;
    _isNotificationCleared = false;

    _isNotification = false;
}

ItemData::ItemData(const ItemData& orig)
{
	this->uid = orig.uid;
	this->date = orig.date;
	this->time = orig.time;
	this->_isReminder = orig._isReminder;
    this->_isNotificationCleared = orig._isNotificationCleared;
	this->textTitle = orig.textTitle;
	this->textDetails = orig.textDetails;

    this->_isNotification = orig._isNotification;
}

ItemData::~ItemData()
{
}

std::string ItemData::toString()
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

    s += textTitle;
    s += ". ";

    if (_isReminder)
        s += "reminder. ";

    if (_isNotificationCleared)
        s += "cleared. ";

    return s;
}

long ItemData::getUid()
{
    return uid;
}

long ItemData::getDate()
{
    return date.getHashCode();
}

long ItemData::getTime()
{
    return time.getHashCode();
}

std::string ItemData::getDateText()
{
    return date.toString();
}

std::string ItemData::getTimeText()
{
    return time.toString();
}

std::string ItemData::getTitle()
{
    return textTitle;
}

std::string ItemData::getDetails()
{
    return textDetails;
}

bool ItemData::isReminder()
{
    return _isReminder;
}

bool ItemData::isNotification()
{
    return _isNotification;
}

bool ItemData::isNotificationCleared()
{
    return _isNotificationCleared;
}

void ItemData::setUid(long value)
{
    uid = value;
}

void ItemData::setDate(DateValue value)
{
    date = value;
}

void ItemData::setTime(TimeValue value)
{
    time = value;
}

void ItemData::setReminder(bool value)
{
    _isReminder = value;
}

void ItemData::setNotification(bool value)
{
    _isNotification = value;
}

void ItemData::setTitle(std::string value)
{
    textTitle = value;
}

void ItemData::setDetails(std::string value)
{
    textDetails = value;
}

//fields definition located in DataManager.notesTableNotesDefinition
void ItemData::setRecord(sql::Record& record)
{
    record.setInteger("date", getDate());
    record.setInteger("time", getTime());
    record.setBool("isReminder", isReminder());
    record.setBool("isNotificationCleared", isNotificationCleared());
    record.setString("title", getTitle());
    record.setString("details", getDetails());
}

//fields definition located in DataManager.notesTableNotesDefinition
void ItemData::parseRecord(sql::Record& record)
{
    this->uid = record.getKeyIdValue()->asInteger();

    this->date = record.getValue("date")->asInteger();
    this->time = record.getValue("time")->asInteger();

    this->_isReminder = record.getValue("isReminder")->asBool();
    this->_isNotificationCleared = record.getValue("isNotificationCleared")->asBool();

    this->textTitle = record.getValue("title")->asString();
    this->textDetails = record.getValue("details")->asString();
}

long ItemData::getDateTime()
{
    return date.getHashCode() * 10000 + time.getHashCode();
}

void ItemData::toogleNotification()
{
    if (isReminder())
    {
        if (isNotificationCleared())
        {
            //enable notification
            _isNotificationCleared = false;
        }
        else
        {
            //disable notification
            _isNotificationCleared = true;
        }
    }
}

void ItemData::clearNotification()
{
    if (isReminder())
    {
        //disable notification
        _isNotificationCleared = true;
    }
}

//note
};
