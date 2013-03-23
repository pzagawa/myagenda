/*
 * File:   NoteItemData.h
 * Author: piotr
 *
 * Created on June 26, 2012, 8:54 PM
 */

#pragma once

#include <string>
#include "DateTimeValue.h"
#include "SqlRecord.h"

namespace note
{

class ItemData
{
private:
	long uid;
	DateValue date;
	TimeValue time;
	bool _isReminder;
	bool _isNotificationCleared;
	std::string textTitle;
	std::string textDetails;

	//field populated runtime, not saved to db
	bool _isNotification;

public:
	ItemData();
	ItemData(const ItemData& orig);
	virtual ~ItemData();
	std::string toString();

public:
	long getUid();
	long getDate();
	long getTime();
	std::string getDateText();
	std::string getTimeText();
	std::string getTitle();
	std::string getDetails();
	bool isReminder();
	bool isNotification();
	bool isNotificationCleared();

public:
	void setUid(long value);
	void setDate(DateValue value);
	void setTime(TimeValue value);
	void setReminder(bool value);
	void setNotification(bool value);
	void setTitle(std::string value);
	void setDetails(std::string value);
	void toogleNotification();
	void clearNotification();

public:
	void setRecord(sql::Record& record);
	void parseRecord(sql::Record& record);
	long getDateTime();

};

//note
};
