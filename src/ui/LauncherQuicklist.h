/*
 * File:   LauncherQuicklist.h
 * Author: piotr
 *
 * Created on August 7, 2012, 7:39 PM
 */

#pragma once

#include <unity/unity/unity.h>
#include <libnotify/notify.h>
#include <libnotify/notification.h>
#include "DataTypes.h"

class LauncherQuicklist
{
private:
	UnityLauncherEntry* unityLauncher;

	DbusmenuMenuitem* quickList;

    DbusmenuMenuitem* mitemNewNote;
    DbusmenuMenuitem* mitemShowNote;
    DbusmenuMenuitem* mitemClearReminder;

	long uidCurrentReminder;

public:
	LauncherQuicklist();
	LauncherQuicklist(const LauncherQuicklist& orig);
	virtual ~LauncherQuicklist();

private:
	Glib::ustring elipsizeNoteTitle(Glib::ustring title);
	DbusmenuMenuitem* addMenuItem(const Glib::ustring& label);

	void setMenuItemShowNote(Glib::ustring itemTitle);
	void setMenuItemClearReminder(Glib::ustring itemTitle);

	void static onMenuItemActivated(DbusmenuMenuitem* item, int time, gpointer data);

public:
	void initialize();
	void update(data::NoteInfoItemList& noteInfoList);

};
