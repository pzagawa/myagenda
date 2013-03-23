/*
 * File:   MainWindow.cpp
 * Author: piotr
 *
 * Created on June 23, 2012, 1:19 PM
 */

#include "MyAgendaApp.h"
#include "MainWindow.h"
#include "MonthViewDayData.h"
#include "MonthViewDayData.h"
#include "NoteItemView.h"
#include "Lang.h"
#include "Utils.h"
#include "Resources.h"
#include "AboutDialog.h"
#include <iostream>

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Window(cobject), ui(refGlade)
{
    notesListPosition = 0;
}

MainWindow::~MainWindow()
{
}

MainWindow* MainWindow::get(const Glib::RefPtr<Gtk::Builder>& ui)
{
    MainWindow* window = NULL;

    ui->get_widget_derived("winMain", window);

    return window;
}

void MainWindow::on_realize()
{
    Gtk::Window::on_realize();

    initialize();

    initializeCalendarView();
}

void MainWindow::on_unrealize()
{
    Gtk::Window::on_unrealize();

}

bool MainWindow::on_delete_event(GdkEventAny* event)
{
    Glib::RefPtr<Gdk::Window> wnd = this->get_window();

    if (wnd)
    {
        Gdk::WindowState state = wnd->get_state();

        const bool isIconify = ((state & Gdk::WINDOW_STATE_ICONIFIED) == Gdk::WINDOW_STATE_ICONIFIED);

        if (isIconify)
        {
            //close window if iconified
            return false;
        }
        else
        {
            //do not close window by default, iconify instead
            wnd->iconify();
            return true;
        }
    }
    else
    {
        //close window if there is a problem with gdk window
        return false;
    }
}

void MainWindow::initialize()
{
    //set app title
    this->set_title(lang::getTitleString());

    //get buttons
    ui->get_widget("btnPrev", btnPrev);
    ui->get_widget("btnNext", btnNext);

    ui->get_widget_derived("btnCurrent", btnCurrent);
    btnCurrent->set_color_rgb_left(0.0, 0.30, 0.60);
    btnCurrent->set_color_rgb_right(0.5, 0.5, 0.5);

    ui->get_widget("btnNewNote", btnNewNote);
    ui->get_widget("btnAbout", btnAbout);

    ui->get_widget_derived("centerSeparator", centerSeparator);
    ui->get_widget_derived("topSeparator", topSeparator);
    ui->get_widget_derived("bottomSeparator", bottomSeparator);

    //get labels
    ui->get_widget_derived("textDayInfo", textDayInfo);
    textDayInfo->set_color_rgb(0.5, 0.1, 0.2);

    ui->get_widget_derived("textDayInfoDetails", textDayInfoDetails);
    textDayInfoDetails->set_color_rgb(0.5, 0.2, 0.3);

    //setup monthView
    ui->get_widget("eventBoxMonthView", eventBoxMonthView);
    eventBoxMonthView->add(monthView);
    eventBoxMonthView->show_all();

    //setup notesView
    ui->get_widget_derived("notesListView", notesView);
    ui->get_widget("scrolledNoteList", scrolledNoteList);

    //connect buttons signals
    btnPrev->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::OnMonthViewPrevButtonClick));
    btnNext->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::OnMonthViewNextButtonClick));
    btnCurrent->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::OnMonthViewCurrentButtonClick));
    btnNewNote->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::OnNewNoteButtonClick));
    btnAbout->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::OnAbountButtonClick));

    //translate ui
    translateUi();

    //activate monthView events
    eventBoxMonthView->add_events(Gdk::BUTTON_PRESS_MASK);
    eventBoxMonthView->add_events(Gdk::BUTTON_RELEASE_MASK);

    //monthView button_release event
    eventBoxMonthView->signal_button_release_event().connect(sigc::mem_fun(this, &MainWindow::OnMonthViewButtonReleaseEvent));

    //month view day selection signal
    monthView.signal_day_selected.connect(sigc::mem_fun(this, &MainWindow::OnMonthViewDaySelected));

    //month view query for month view
    monthView.signal_query_for_data.connect(sigc::mem_fun(this, &MainWindow::OnMonthViewQueryForData));

    //list ready after loading signal
    notesView->signal_size_allocate().connect(sigc::mem_fun(this, &MainWindow::OnNotesViewListReady));

    //on notes list item button click
    notesView->signal_item_button_clicked.connect(sigc::mem_fun(this, &MainWindow::OnNotesListItemButtonClick));

    //connect to app timer
    MyAgendaApp::app->getTimer()->connect(sigc::mem_fun(this, &MainWindow::OnAppTimerTick));
}

void MainWindow::translateUi()
{
    btnNewNote->set_tooltip_text(lang::getString(lang::SHORTCUT_NEW_NOTE));
}

void MainWindow::setDayInfoText(std::string text)
{
    textDayInfo->set_color_rgb(0.5, 0.1, 0.2);
    textDayInfoDetails->set_color_rgb(0.3, 0.3, 0.3);

    textDayInfo->set_label(text);
}

void MainWindow::setDayInfoDetailsText(std::string text)
{
    textDayInfoDetails->set_label(text);
}

void MainWindow::initializeCalendarView()
{
    monthViewDate.set_time_current();
    monthView.setViewAndSelectDate(monthViewDate);
    btnCurrent->setText(monthView.getCurrentMonthNameText(), monthView.getCurrentMonthYearText());
}

void MainWindow::updateCalendarView()
{
    monthView.setViewDate(monthViewDate);
    btnCurrent->setText(monthView.getCurrentMonthNameText(), monthView.getCurrentMonthYearText());
}

void MainWindow::setCalendarViewToday()
{
    monthViewDate.set_time_current();
    updateCalendarView();
}

void MainWindow::setCalendarViewNextMonth()
{
    monthViewDate.add_months(1);
    updateCalendarView();
}

void MainWindow::setCalendarViewPrevMonth()
{
    monthViewDate.subtract_months(1);
    updateCalendarView();
}

void MainWindow::OnMonthViewPrevButtonClick()
{
    setCalendarViewPrevMonth();
}

void MainWindow::OnMonthViewNextButtonClick()
{
    setCalendarViewNextMonth();
}

void MainWindow::OnMonthViewCurrentButtonClick()
{
    setCalendarViewToday();
}

bool MainWindow::OnMonthViewButtonReleaseEvent(GdkEventButton* event)
{
    cal::MonthViewDayData* data = monthView.getDayData(event->x, event->y);

    if (data)
        monthView.setSelectedDate(data->getDate());

    return true;
}

void MainWindow::OnMonthViewDaySelected(cal::MonthViewDayData* dayData)
{
    //do not restore position on date change
    notesListPosition = -1;

    loadNotesToListView(dayData->getDateValue());
}

void MainWindow::loadNotesToListView(DateValue date)
{
    setDayInfoText(monthView.getSelectedDateText());
    setDayInfoDetailsText("...");

    //load notes to list
    data::NoteList noteList;

    MyAgendaApp::app->getDataManager().getNotesForDay(date, noteList);

    notesView->clear();

    int remindersCount = 0;

    for (int index = 0; index < noteList.size(); index++)
    {
        note::ItemData& itemData = noteList.at(index);

        notesView->addItem(itemData);

        if (itemData.isReminder() && itemData.isNotification() && !itemData.isNotificationCleared())
            remindersCount++;
    }

    notesView->restoreSelection();

    //update info label
    setDayInfoDetailsText(lang::getDayInfoDetailsString(remindersCount, noteList.size()));
}

void MainWindow::OnNotesViewListReady(Gdk::Rectangle allocation)
{
    //scroll list down after loading
    Glib::RefPtr<Gtk::Adjustment> adj = scrolledNoteList->get_vadjustment();

    //if position not stored, scroll list to bottom
    if (notesListPosition == -1)
    {
        adj->set_value(adj->get_upper());
    }
    else
    {
        //restore position
        adj->set_value(notesListPosition);
        notesListPosition = -1;
    }
}

void MainWindow::updateUiOnDataChange(bool scrollToBottom)
{
    Glib::Mutex::Lock lock(mutexUpdateUi);

    if (scrollToBottom)
    {
        notesListPosition = -1;
    }
    else
    {
        //save notes list position to be restored in OnNotesViewListReady
        notesListPosition = scrolledNoteList->get_vadjustment()->get_value();
    }

    //list reload
    loadNotesToListView(monthView.getSelectedDate());

    //reload month view
    monthView.triggerMonthSelectionEvent();

    //update unity notifications
    MyAgendaApp::app->updateUnityNotifications();
}

void MainWindow::OnNewNoteButtonClick()
{
    //show dialog to add new note
    DateValue selectedDate = monthView.getSelectedDate();

    note::ItemData noteData;

    const int response = EditNoteDialog::create(this, &noteData, &selectedDate);

    if (response == Gtk::RESPONSE_ACCEPT)
    {
        MyAgendaApp::app->getDataManager().addNote(noteData);
        updateUiOnDataChange(true);
    }
}

void MainWindow::OnNotesListItemButtonClick(long noteUid, int buttonId)
{
    //get note item object to process
    note::ItemData noteData;

    if (!MyAgendaApp::app->getDataManager().getNote(noteUid, noteData))
    {
        std::cerr << "can't find note for edit/delete with uid: " << noteUid << std::endl;
        return;
    }

    //check if note edit clicked
    if (buttonId == note::ItemView::BUTTON_ID_EDIT)
    {
        //show dialog to edit note
        const int response = EditNoteDialog::create(this, &noteData, NULL);

        if (response == Gtk::RESPONSE_ACCEPT)
        {
            MyAgendaApp::app->getDataManager().updateNote(noteData);
            updateUiOnDataChange(false);
        }

        if (response == Gtk::RESPONSE_REJECT)
        {
            MyAgendaApp::app->getDataManager().deleteNote(noteUid);
            updateUiOnDataChange(false);
        }
    }

    //check if note delete clicked
    if (buttonId == note::ItemView::BUTTON_ID_DELETE)
    {
        MyAgendaApp::app->getDataManager().deleteNote(noteUid);
        updateUiOnDataChange(false);
    }

    //check if note notification has been cleared
    if (buttonId == note::ItemView::BUTTON_ID_TOGGLE_NOTIFICATION)
    {
        if (noteData.isReminder())
        {
            noteData.toogleNotification();
            MyAgendaApp::app->getDataManager().updateNote(noteData);
            updateUiOnDataChange(false);
        }
    }
}

void MainWindow::OnMonthViewQueryForData(Glib::Date dtBegin, Glib::Date dtEnd, data::NoteInfoSummaryMap& summaryMap)
{
    DateValue dateBegin = dtBegin;
    DateValue dateEnd = dtEnd;

    MyAgendaApp::app->getDataManager().getNotesForMonthView(dateBegin, dateEnd, summaryMap);
}

bool MainWindow::OnAppTimerTick()
{
    static DateTimeValue storedValue = DateTimeValue::zero();

    DateTimeValue nowValue = DateTimeValue::now();

    //save CPU; process only if time changed with minute resolution
    if (nowValue.getHashCode() != storedValue.getHashCode())
    {
        storedValue = nowValue;

        //update UI
        updateUiOnDataChange(false);
    }

    return true;
}

void MainWindow::OnAbountButtonClick()
{
    const int response = AboutDialog::create(*this);
}

void MainWindow::updateTarget(int message_id, void* data)
{
    if (message_id == MessageDispatcher::NEW_NOTE)
    {
        execMenuItemNewNote();
    }

    if (message_id == MessageDispatcher::SHOW_NOTE)
    {
        long noteUid = (long)data;
        execMenuItemShowNote(noteUid);
    }

    if (message_id == MessageDispatcher::CLEAR_REMINDER)
    {
        long noteUid = (long)data;
        execMenuItemClearReminder(noteUid);
    }
}

void MainWindow::execMenuItemNewNote()
{
    note::ItemData noteData;

    DateValue selectedDate = DateValue::now();

    const int response = EditNoteDialog::create(this, &noteData, &selectedDate);

    if (response == Gtk::RESPONSE_ACCEPT)
    {
        MyAgendaApp::app->getDataManager().addNote(noteData);
        updateUiOnDataChange(true);
    }
}

void MainWindow::execMenuItemShowNote(long noteUid)
{
    //get note item object to process
    note::ItemData noteData;
    if (MyAgendaApp::app->getDataManager().getNote(noteUid, noteData))
    {
        //show dialog to edit note
        const int response = EditNoteDialog::create(this, &noteData, NULL);

        if (response == Gtk::RESPONSE_ACCEPT)
        {
            MyAgendaApp::app->getDataManager().updateNote(noteData);
            updateUiOnDataChange(false);
        }

        if (response == Gtk::RESPONSE_REJECT)
        {
            MyAgendaApp::app->getDataManager().deleteNote(noteUid);
            updateUiOnDataChange(false);
        }
    }
    else
    {
        std::cerr << "can't find note to edit with uid: " << noteUid << std::endl;
    }
}

void MainWindow::execMenuItemClearReminder(long noteUid)
{
    //get note item object to process
    note::ItemData noteData;
    if (MyAgendaApp::app->getDataManager().getNote(noteUid, noteData))
    {
        if (noteData.isReminder())
        {
            noteData.clearNotification();
            MyAgendaApp::app->getDataManager().updateNote(noteData);
            updateUiOnDataChange(false);
        }
    }
    else
    {
        std::cerr << "can't find note to reminder clearing with uid: " << noteUid << std::endl;
    }
}
