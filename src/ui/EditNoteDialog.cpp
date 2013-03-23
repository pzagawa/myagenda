/*
 * File:   EditNoteDialog.cpp
 * Author: piotr
 *
 * Created on June 30, 2012, 23:39 PM
 */

#include <iostream>
#include "EditNoteDialog.h"
#include "Lang.h"
#include "MyAgendaApp.h"
#include "DateTimeValue.h"
#include "Preferences.h"

EditNoteDialog::EditNoteDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Dialog(cobject), ui(refGlade)
{
	mode = CREATE_NEW;
    isInputDataValid = false;
}

EditNoteDialog::~EditNoteDialog()
{
}

int EditNoteDialog::create(Window* parent, note::ItemData* noteData, DateValue* selectedDate)
{
    static int ref_counter = 0;

    //allow only one instance at a time
    if (ref_counter > 0)
        return Gtk::RESPONSE_CANCEL;

    //manage auto ref count
    RefGuard refGuard(&ref_counter);

    EditNoteDialog* dialog = NULL;

    //load and create dialog
    const Glib::RefPtr<Gtk::Builder> ui = MyAgendaApp::app->getUiBuilder();
    const std::string& fileName = MyAgendaApp::app->getUiFileNamePath();

    try
    {
        Glib::RefPtr<Gtk::Builder> uiDialog = ui->create_from_file(fileName,"dlgNoteEdit");
        uiDialog->get_widget_derived("dlgNoteEdit", dialog);

        if (parent)
            dialog->set_transient_for(*parent);

        dialog->set_modal(true);
        dialog->set_position(Gtk::WIN_POS_CENTER_ON_PARENT);

    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    //initialize
    dialog->noteData = noteData;

    if (selectedDate)
    {
        dialog->mode = CREATE_NEW;
        dialog->selectedDate = *selectedDate;
    }
    else
    {
        dialog->mode = EDIT;
    }

    //show and get result
    const int response = dialog->run();

    dialog->hide();

    delete dialog;

    return response;
}

void EditNoteDialog::on_realize()
{
    Gtk::Window::on_realize();

    initialize();

    setInputData();

    verifyInputData();

    initializeEvents();
}

void EditNoteDialog::initialize()
{
    //set app title
    this->set_title(lang::getNoteDialogTitleString(mode));

    //get labels
    ui->get_widget("labelTitle", labelTitle);
    ui->get_widget("labelDescription", labelDescription);
    ui->get_widget("labelDate", labelDate);
    ui->get_widget("labelTime", labelTime);
    ui->get_widget("labelReminder", labelReminder);

    //get controls
    ui->get_widget_derived("infoBar", infoBar);
    ui->get_widget("entryTitle", entryTitle);
    ui->get_widget("textDescription", textDescription);
    ui->get_widget("entryDate", entryDate);
    ui->get_widget("entryTime", entryTime);
    ui->get_widget("checkReminder", checkReminder);

    //get buttons
    ui->get_widget("btnDelete", btnDelete);
    ui->get_widget("btnSave", btnSave);
    ui->get_widget("btnCancel", btnCancel);

    //delete button visibile only for edit mode
    btnDelete->set_visible(mode == EDIT);

    textDescription->set_wrap_mode(Gtk::WRAP_WORD);

    //translate ui
    translateUi();
}

void EditNoteDialog::initializeEvents()
{
    //connect buttons signals
    btnDelete->signal_clicked().connect(sigc::mem_fun(this, &EditNoteDialog::OnButtonDeleteClick));
    btnSave->signal_clicked().connect(sigc::mem_fun(this, &EditNoteDialog::OnButtonSaveClick));
    btnCancel->signal_clicked().connect(sigc::mem_fun(this, &EditNoteDialog::OnButtonCancelClick));

    //connect data input signals
    entryTitle->signal_changed().connect(sigc::mem_fun(this, &EditNoteDialog::OnTitleEntryChanged));
    entryDate->signal_changed().connect(sigc::mem_fun(this, &EditNoteDialog::OnDateEntryChanged));
    entryTime->signal_changed().connect(sigc::mem_fun(this, &EditNoteDialog::OnTimeEntryChanged));
}

void EditNoteDialog::translateUi()
{
    labelTitle->set_label(lang::getString(lang::EDIT_NOTE_TITLE));
    labelDescription->set_label(lang::getString(lang::EDIT_NOTE_DESCRIPTION));
    labelDate->set_label(lang::getString(lang::EDIT_NOTE_DATE));
    labelTime->set_label(lang::getString(lang::EDIT_NOTE_TIME));
    labelReminder->set_label(lang::getString(lang::EDIT_NOTE_REMINDER));
    checkReminder->set_label(lang::getString(lang::EDIT_NOTE_REMINDER_CHECK));

    btnSave->set_tooltip_text(lang::getString(lang::SHORTCUT_ACCEPT));

    //set information label
    if (mode == CREATE_NEW)
    {
        infoBar->setText(Gtk::MESSAGE_INFO, lang::getString(lang::EDIT_NOTE_INFORMATION));
    }
    else
    {
        infoBar->setText(Gtk::MESSAGE_INFO, lang::getString(lang::EDIT_NOTE_INFORMATION));
    }

    //set tooltips
    entryDate->set_tooltip_text(lang::getString(lang::ENTER_DATE_IN_FORMAT));
    entryTime->set_tooltip_text(lang::getString(lang::ENTER_TIME_IN_FORMAT));
}

void EditNoteDialog::OnButtonDeleteClick()
{
    this->response(Gtk::RESPONSE_REJECT);
}

void EditNoteDialog::OnButtonSaveClick()
{
    verifyInputData();

    this->response(Gtk::RESPONSE_ACCEPT);
}

void EditNoteDialog::OnButtonCancelClick()
{
    this->response(Gtk::RESPONSE_CANCEL);
}

void EditNoteDialog::OnTitleEntryChanged()
{
    verifyInputData();
}

void EditNoteDialog::OnDateEntryChanged()
{
    verifyInputData();
}

void EditNoteDialog::OnTimeEntryChanged()
{
    verifyInputData();
}

void EditNoteDialog::verifyInputData()
{
    const Glib::ustring title = entryTitle->get_text();
    const Glib::ustring desc = textDescription->get_buffer()->get_text(false);
    const Glib::ustring date = entryDate->get_text();
    const Glib::ustring time = entryTime->get_text();
    const bool isReminder = checkReminder->get_active();

    bool title_valid = false;
    bool date_valid = false;
    bool time_valid = false;

    //check title
    if (title.length() > 0)
    {
        title_valid = true;
    }

    //check date
    DateValue dateValue;
    if (dateValue.parseString(date))
    {
        date_valid = true;
    }

    //check time
    TimeValue timeValue;
    if (timeValue.parseString(time))
    {
        time_valid = true;
    }

    if (title_valid && date_valid && time_valid)
    {
        isInputDataValid = true;

        btnSave->set_sensitive(true);
        infoBar->setText(Gtk::MESSAGE_INFO, lang::getString(lang::EDIT_NOTE_INPUT_VALIDATED));

        //update note data
        noteData->setDate(dateValue);
        noteData->setTime(timeValue);
        noteData->setReminder(isReminder);
        noteData->setTitle(title);
        noteData->setDetails(desc);
    }
    else
    {
        isInputDataValid = false;

        btnSave->set_sensitive(false);

        std::string message = lang::getString(lang::EDIT_NOTE_INPUT_NOT_VALIDATED);

        if (!title_valid)
            message = lang::getString(lang::EDIT_NOTE_INPUT_CORRECT_TITLE);

        if (title_valid && !date_valid)
            message = lang::getString(lang::EDIT_NOTE_INPUT_CORRECT_DATE);

        if (title_valid && date_valid && !time_valid)
            message = lang::getString(lang::EDIT_NOTE_INPUT_CORRECT_TIME);

        infoBar->setText(Gtk::MESSAGE_ERROR, message);
    }
}

void EditNoteDialog::setInputData()
{
    //initialize inputs for new note
    if (mode == CREATE_NEW)
    {
        //set date field value to selected date
        entryDate->set_text(selectedDate.toString());

        //initialize time field as current time +15min
        Glib::DateTime dateTime = Glib::DateTime::create_now_local().add_minutes(Preferences::prefs->getNewNoteMinutes());
        TimeValue timeValue = dateTime;
        entryTime->set_text(timeValue.toString());
    }

    //initialize inputs from existing note
    if (mode == EDIT)
    {
        entryTitle->set_text(noteData->getTitle());
        textDescription->get_buffer()->set_text(noteData->getDetails());
        entryDate->set_text(noteData->getDateText());
        entryTime->set_text(noteData->getTimeText());
        checkReminder->set_active(noteData->isReminder());
    }

}
