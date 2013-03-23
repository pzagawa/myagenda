/*
 * File:   NoteInfoItem.h
 * Author: piotr
 *
 * Created on July 5, 2012, 0:29 AM
 */

#pragma once

#include <string>
#include "DateTimeValue.h"
#include "SqlRecord.h"

class NoteInfoItem
{
private:
	long uid;
	DateValue date;
	TimeValue time;
	bool _isReminder;
	bool _isNotificationCleared;

public:
	NoteInfoItem();
	NoteInfoItem(const NoteInfoItem& orig);
	NoteInfoItem& operator=(NoteInfoItem& orig);
	virtual ~NoteInfoItem();
	std::string toString();

public:
	long getUid();
	long getDate();
	long getTime();
	bool isReminder();
	bool isNotificationCleared();

public:
	void reset();
	void parseRecord(sql::Record& record);
	long getDateTime()  const;

};
