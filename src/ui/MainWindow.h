/*
 * File:   MainWindow.h
 * Author: piotr
 *
 * Created on June 23, 2012, 1:19 PM
 */

#pragma once

#include <gtkmm.h>
#include <string>
#include "DataTypes.h"
#include "MonthView.h"
#include "MonthViewDayData.h"
#include "TitleButton.h"
#include "NoteListView.h"
#include "EditNoteDialog.h"
#include "CustomLabel.h"
#include "CustomSeparator.h"
#include "MessageDispatcher.h"

class MainWindow
	: public Gtk::Window, public MessageDispatcher
{
private:
	Glib::RefPtr<Gtk::Builder> ui;

	Gtk::Button* btnPrev;
	TitleButton* btnCurrent;
	Gtk::Button* btnNext;

	Gtk::Button* btnNewNote;
	Gtk::Button* btnAbout;

	Gtk::Box* boxMonthView;

	CustomLabel* textDayInfo;
	CustomLabel* textDayInfoDetails;

	CustomSeparator* centerSeparator;
	CustomSeparator* topSeparator;
	CustomSeparator* bottomSeparator;

	Gtk::EventBox* eventBoxMonthView;
	Gtk::ScrolledWindow* scrolledNoteList;

	Glib::Date monthViewDate;
	cal::MonthView monthView;

	note::ListView* notesView;
	double notesListPosition;

	Glib::Mutex mutexUpdateUi;

public:
	MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~MainWindow();

	static MainWindow* get(const Glib::RefPtr<Gtk::Builder>& ui);

	void updateTarget(int message_id, void* data);

private:
	virtual void on_realize();
	virtual void on_unrealize();
	virtual bool on_delete_event(GdkEventAny* event);

private:
	void initialize();
	void translateUi();
	void updateCalendarView();
	void setDayInfoText(std::string text);
	void setDayInfoDetailsText(std::string text);
	void initializeCalendarView();
	void setCalendarViewToday();
	void setCalendarViewNextMonth();
	void setCalendarViewPrevMonth();
	void loadNotesToListView(DateValue date);
	void updateUiOnDataChange(bool scrollToBottom);

private:
	void OnMonthViewPrevButtonClick();
	void OnMonthViewNextButtonClick();
	void OnMonthViewCurrentButtonClick();
	void OnNewNoteButtonClick();
	void OnAbountButtonClick();
	bool OnMonthViewButtonReleaseEvent(GdkEventButton* event);
	void OnMonthViewDaySelected(cal::MonthViewDayData* dayData);
	void OnMonthViewQueryForData(Glib::Date dtBegin, Glib::Date dtEnd, data::NoteInfoSummaryMap& summaryMap);
	void OnNotesViewListReady(Gdk::Rectangle allocation);
	void OnNotesListItemButtonClick(long noteUid, int buttonId);
	bool OnAppTimerTick();
	bool OnAppIdleTimerTick();

private:
	void execMenuItemNewNote();
	void execMenuItemShowNote(long noteUid);
	void execMenuItemClearReminder(long noteUid);

};
