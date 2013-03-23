/*
 * File:   MyAgendaApp.h
 * Author: piotr
 *
 * Created on June 22, 2012, 8:32 PM
 */

#pragma once

#include <gtkmm.h>
#include <string>
#include "Preferences.h"
#include "DataManager.h"
#include "NotificationManager.h"
#include "LauncherQuicklist.h"
#include "MessageDispatcher.h"

class MyAgendaApp
	: public Gtk::Application, public MessageDispatcher
{
public:
	const static Glib::ustring APP_ID;

public:
	static MyAgendaApp* app;

private:
	Glib::RefPtr<Glib::TimeoutSource> timer;
    Glib::RefPtr<Gtk::Builder> ui;

	Preferences preferences;
	DataManager dataManager;
	NotificationManager notifyManager;
	LauncherQuicklist quicklist;

public:
	std::vector<MessageDispatcher*> messageTargets;

public:
	MyAgendaApp(int argc, char** argv);
	virtual ~MyAgendaApp();

public:
	void loadUi();
	void initialize();
	void run(Gtk::Window& window);
	bool isAlreadyRunning();

	void updateUnityNotifications();

	void addMessageTarget(MessageDispatcher* messageTarget);
	void updateTarget(int message_id, void* data);

public:
	std::string getUiDirectory();
	std::string getUiFileNamePath();
	std::string getUserDirectory();
	std::string getDataDirectory();
	std::string getDatabaseFileNamePath();
	std::string getAppIconFileNamePath();

public:
	Glib::RefPtr<Glib::TimeoutSource> getTimer();
	Glib::RefPtr<Gtk::Builder> getUiBuilder();
	Glib::RefPtr<Gdk::Pixbuf> loadImage(std::string name);
	DataManager& getDataManager();

private:
	void OnActivation();

};
