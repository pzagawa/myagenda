/*
 * File:   EditNoteDialog.h
 * Author: piotr
 *
 * Created on June 30, 2012, 23:39 PM
 */

#pragma once

#include <gtkmm.h>
#include "CustomInfoBar.h"
#include "NoteItemData.h"

class EditNoteDialog
	: public Gtk::Dialog
{
public:
	enum Mode
	{
		CREATE_NEW,
		EDIT,
	};

private:
	Mode mode;
    DateValue selectedDate;
	bool isInputDataValid;
	note::ItemData* noteData;

	Glib::RefPtr<Gtk::Builder> ui;

	CustomInfoBar* infoBar;

	Gtk::Label* labelTitle;
	Gtk::Label* labelDescription;
	Gtk::Label* labelDate;
	Gtk::Label* labelTime;
	Gtk::Label* labelReminder;

	Gtk::Entry* entryTitle;
	Gtk::TextView* textDescription;
	Gtk::Entry* entryDate;
	Gtk::Entry* entryTime;
	Gtk::CheckButton* checkReminder;

	Gtk::Button* btnDelete;
	Gtk::Button* btnSave;
	Gtk::Button* btnCancel;

public:
	EditNoteDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~EditNoteDialog();

	static int create(Window* parent, note::ItemData* noteData, DateValue* selectedDate);

private:
	virtual void on_realize();

private:
	void initialize();
	void initializeEvents();
	void translateUi();
	void setInputData();
	void verifyInputData();

private:
	void OnButtonDeleteClick();
	void OnButtonSaveClick();
	void OnButtonCancelClick();
	void OnTitleEntryChanged();
	void OnDateEntryChanged();
	void OnTimeEntryChanged();

};
