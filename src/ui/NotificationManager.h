/*
 * File:   NotificationManager.h
 * Author: piotr
 *
 * Created on July 9, 2012, 10:43 PM
 */

#pragma once

#include <unity/unity/unity.h>
#include <libnotify/notify.h>
#include <libnotify/notification.h>
#include "DataTypes.h"

class NotificationManager
{
private:
	UnityLauncherEntry* unityLauncher;

public:
	NotificationManager();
	NotificationManager(const NotificationManager& orig);
	virtual ~NotificationManager();

private:
	int getUpdateTimeoutSeconds();
	int getRemindersCountForToday(data::NoteInfoItemList& noteInfoList);
	void showNotification(std::string title, std::string text);
	bool hasNotificationTextChanged(std::string title, std::string text);
	bool createNotificationText(data::NoteInfoItemList& noteInfoList, std::string& title, std::string& text);
	void updateUnityLauncher(int count);

public:
	void updateUnityNotifications(data::NoteInfoItemList& noteInfoList);

};
