/*
 * File:   Lang.h
 * Author: piotr
 *
 * Created on June 24, 2012, 2:13 PM
 */

#include "EditNoteDialog.h"
#include "Resources.h"
#include "Utils.h"

#pragma once

namespace lang
{
	enum
	{
		DLG_TITLE_NEW_NOTE,
		DLG_TITLE_EDIT_NOTE,

		EDIT_NOTE_INFORMATION,

		EDIT_NOTE_TITLE,
		EDIT_NOTE_DESCRIPTION,
		EDIT_NOTE_DATE,
		EDIT_NOTE_TIME,
		EDIT_NOTE_REMINDER,
		EDIT_NOTE_REMINDER_CHECK,

		SHORTCUT_NEW_NOTE,
		SHORTCUT_ACCEPT,

		DATE_FORMAT,
		TIME_FORMAT,

		ENTER_DATE_IN_FORMAT,
		ENTER_TIME_IN_FORMAT,

		EDIT_NOTE_INPUT_VALIDATED,
		EDIT_NOTE_INPUT_NOT_VALIDATED,
		EDIT_NOTE_INPUT_CORRECT_TITLE,
		EDIT_NOTE_INPUT_CORRECT_DATE,
		EDIT_NOTE_INPUT_CORRECT_TIME,

		NOTES_INFO_NONE,
		NOTES_INFO_COUNT,
		NOTES_REMINDERS_COUNT,

		NOTIFY_TEXT_REMINDER_TODAY,
		NOTIFY_TEXT_REMINDER_OLD1,
		NOTIFY_TEXT_REMINDER_OLD2,

		BTN_ABOUT,
		BTN_NEW_NOTE,

		LAUNCHER_NEW_NOTE,
		LAUNCHER_SHOW_NOTE,
		LAUNCHER_CLEAR_REMINDER,

		WELCOME_NOTE_TITLE,
		WELCOME_NOTE_DETAILS,
	};

	static const Glib::ustring strings[] =
	{
		"new note",
		"edit note",

		"Enter note data",

		"Title",
		"Description",
		"Date",
		"Time",
		"Reminder",
		"remind the specified time",

		"shortcut: <ctrl+n>",
		"shortcut: <enter>",

		//date format: ISO 8601
		"YYYY-MM-DD",
		//time format: ISO 8601
		"hh:mm",

		"enter date in format: YYYY-MM-DD",
		"enter time in format: hh:mm",

		"Note is ready to save",
        "Please correct note data",
		"Enter note title",
		"Enter correct note date",
		"Enter correct note time",

        "no notes for this day",
        "notes: ",
		"reminders: ",

		" reminder(s) today",
		" old",
		" old reminder(s)",

		"about",
		"new note",

		"New Note",
		"Show Note",
		"Clear Reminder: ",

		"Welcome to MyAgenda!",

		"You can store notes for each day and also set reminders to them. "
			"Clear any reminder with quicklist menu or by clicking on note reminder icon in list.\n"
			"FAQ:\n"
			"where MyAgenda stores data?\n"
			"MyAgenda is using '.config' directory placed in user's home directory, where it stores its SQLite database file. "
			"Full path: ~/.config/myagenda/data.sqlite.",
	};

	static const Glib::ustring& getString(int id)
	{
		return strings[id];
	};

	static const Glib::ustring getTitleString(const Glib::ustring& suffix = "")
	{
		Glib::ustring s = Resources::res->app_name;
		s += " ";
		s += Resources::res->app_version;

		if (suffix.length() > 0)
		{
			s += " - ";
			s += suffix;
		}

		return s;
	};

	static const Glib::ustring getNoteDialogTitleString(const EditNoteDialog::Mode mode)
	{
		if (mode == EditNoteDialog::CREATE_NEW)
			return getTitleString(getString(DLG_TITLE_NEW_NOTE));

		if (mode == EditNoteDialog::EDIT)
			return getTitleString(getString(DLG_TITLE_EDIT_NOTE));

		return getTitleString();
	}

	static const Glib::ustring getDayInfoDetailsString(int remindersCount, int notesCount)
	{
		std::string text = "";

		if (notesCount == 0)
		{
			text += lang::getString(NOTES_INFO_NONE);
		}
		else
		{
			if (remindersCount > 0)
			{
				text += getString(NOTES_REMINDERS_COUNT);
				text += utils::numToString(remindersCount);
				text += ", ";
			}

			text += getString(NOTES_INFO_COUNT);
			text += utils::numToString(notesCount);
		}

		return text;
	}

	static const Glib::ustring getNotificationString(int todayCount, int othersCount)
	{
		std::string text = "";

		if (todayCount > 0)
			text += utils::numToString(todayCount) + getString(NOTIFY_TEXT_REMINDER_TODAY);

		if (othersCount > 0)
		{
			if (text.length() > 0)
			{
				text += ", " + utils::numToString(othersCount) + getString(NOTIFY_TEXT_REMINDER_OLD1);
			}
			else
			{
				text += utils::numToString(othersCount) + getString(NOTIFY_TEXT_REMINDER_OLD2);
			}
		}

		return text;
	}

};
