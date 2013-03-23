/*
 * File:   MyAgendaApp.cpp
 * Author: piotr
 *
 * Created on June 22, 2012, 8:32 PM
 */

#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtkmm/enums.h>
#include <gtkmm/settings.h>
#include "MyAgendaApp.h"
#include "Resources.h"
#include "Utils.h"
#include "Lang.h"

const Glib::ustring MyAgendaApp::APP_ID = "pl.piotr.zagawa.myagenda";

MyAgendaApp* MyAgendaApp::app = NULL;

MyAgendaApp::MyAgendaApp(int argc, char** argv)
    : Gtk::Application(argc, argv, MyAgendaApp::APP_ID, Gio::APPLICATION_FLAGS_NONE)
{
    app = this;

    this->ui = Gtk::Builder::create();

    //enable gtk button images
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    settings->set_property("gtk_button_images", true);

    //create main data requery timer
    timer = Glib::TimeoutSource::create(1000 * 1);

    //register app
    this->register_application();
}

MyAgendaApp::~MyAgendaApp()
{
}

std::string MyAgendaApp::getUserDirectory()
{
    std::string s = Glib::getenv("HOME");

    if (s.length() == 0)
        s = Glib::get_home_dir();

    return s;
}

std::string MyAgendaApp::getUiDirectory()
{
    return "/opt/extras.ubuntu.com/myagenda/ui";
}

std::string MyAgendaApp::getUiFileNamePath()
{
    return Glib::build_filename(getUiDirectory(), "ui.glade");
}

std::string MyAgendaApp::getAppIconFileNamePath()
{
    return Glib::build_filename(getUiDirectory(), "myagenda.svg");
}

std::string MyAgendaApp::getDataDirectory()
{
    return Glib::build_filename(getUserDirectory(), ".config", "myagenda");
}

std::string MyAgendaApp::getDatabaseFileNamePath()
{
    return Glib::build_filename(getDataDirectory(), "data.sqlite");
}

void MyAgendaApp::initialize()
{
    //connect app signals
    this->signal_activate().connect(sigc::mem_fun(this, &MyAgendaApp::OnActivation));

    //create application config directory
    mkdir(getDataDirectory().c_str(),0777);

    //initialize database
    dataManager.initialize(getDatabaseFileNamePath());

    //initialize quicklist
    quicklist.initialize();
}

void MyAgendaApp::loadUi()
{
    const std::string& fileName = getUiFileNamePath();

    try
    {
        ui->add_from_file(fileName);
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
}

Glib::RefPtr<Gdk::Pixbuf> MyAgendaApp::loadImage(std::string name)
{
    std::string fileName = Glib::build_filename(getUiDirectory(), name);
    return Gdk::Pixbuf::create_from_file(fileName);
}

void MyAgendaApp::run(Gtk::Window& window)
{
    timer->attach();

    this->add_window(window);

    Gtk::Application::run(window);
}

Glib::RefPtr<Gtk::Builder> MyAgendaApp::getUiBuilder()
{
    return ui;
}

DataManager& MyAgendaApp::getDataManager()
{
    return dataManager;
}

Glib::RefPtr<Glib::TimeoutSource> MyAgendaApp::getTimer()
{
    return timer;
}

void MyAgendaApp::updateUnityNotifications()
{
    data::NoteInfoItemList noteInfoList;

    MyAgendaApp::app->getDataManager().getReminders(noteInfoList);

    notifyManager.updateUnityNotifications(noteInfoList);

    quicklist.update(noteInfoList);
}

void MyAgendaApp::addMessageTarget(MessageDispatcher* messageTarget)
{
    messageTargets.push_back(messageTarget);
}

void MyAgendaApp::updateTarget(int message_id, void* data)
{
    for (int index = 0; index < messageTargets.size(); index++)
    	messageTargets.at(index)->updateTarget(message_id, data);
}

bool MyAgendaApp::isAlreadyRunning()
{
    return this->is_remote();
}

void MyAgendaApp::OnActivation()
{
    std::vector<Gtk::Window*> list = this->get_windows();

    if (list.size() > 0)
    {
        Gtk::Window* window = list.at(0);
        window->present();
    }
}
