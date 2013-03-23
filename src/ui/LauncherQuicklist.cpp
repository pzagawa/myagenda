/*
 * File:   LauncherQuicklist.h
 * Author: piotr
 *
 * Created on August 7, 2012, 7:39 PM
 */

#include "LauncherQuicklist.h"
#include "MyAgendaApp.h"
#include "Lang.h"
#include "Preferences.h"
#include "EditNoteDialog.h"

LauncherQuicklist::LauncherQuicklist()
{
    //get unity launcher
    unityLauncher = unity_launcher_entry_get_for_desktop_id("myagenda.desktop");

    uidCurrentReminder = 0;
}

LauncherQuicklist::LauncherQuicklist(const LauncherQuicklist& orig)
{
}

LauncherQuicklist::~LauncherQuicklist()
{
}

DbusmenuMenuitem* LauncherQuicklist::addMenuItem(const Glib::ustring& label)
{
    //menu item: NEW NOTE
    DbusmenuMenuitem* menuItem = dbusmenu_menuitem_new();

    dbusmenu_menuitem_property_set(menuItem, DBUSMENU_MENUITEM_PROP_LABEL, label.c_str());
    dbusmenu_menuitem_property_set_bool(menuItem, DBUSMENU_MENUITEM_PROP_ENABLED, true);
    dbusmenu_menuitem_property_set_bool(menuItem, DBUSMENU_MENUITEM_PROP_VISIBLE, false);

    g_signal_connect(menuItem, DBUSMENU_MENUITEM_SIGNAL_ITEM_ACTIVATED, G_CALLBACK(onMenuItemActivated), this);

    dbusmenu_menuitem_child_append(this->quickList, menuItem);

    return menuItem;
}

void LauncherQuicklist::initialize()
{
    this->quickList = dbusmenu_menuitem_new();

    //menu item: NEW NOTE
    this->mitemNewNote = addMenuItem(lang::getString(lang::LAUNCHER_NEW_NOTE));

    //menu item: SHOW NOTE
    this->mitemShowNote = addMenuItem(lang::getString(lang::LAUNCHER_SHOW_NOTE));

    //menu item: CLEAR REMINDER
    this->mitemClearReminder = addMenuItem(lang::getString(lang::LAUNCHER_CLEAR_REMINDER));

    //set custom menu
    unity_launcher_entry_set_quicklist(unityLauncher, quickList);
}

void LauncherQuicklist::onMenuItemActivated(DbusmenuMenuitem* item, int time, gpointer data)
{
    LauncherQuicklist* caller = (LauncherQuicklist*)data;

    if (item == caller->mitemNewNote)
    {
        MyAgendaApp::app->updateTarget(MessageDispatcher::NEW_NOTE, NULL);
        return;
    }

    if (item == caller->mitemShowNote)
    {
        MyAgendaApp::app->updateTarget(MessageDispatcher::SHOW_NOTE, (void*)caller->uidCurrentReminder);
        return;
    }

    if (item == caller->mitemClearReminder)
    {
        MyAgendaApp::app->updateTarget(MessageDispatcher::CLEAR_REMINDER, (void*)caller->uidCurrentReminder);
        return;
    }
}

Glib::ustring LauncherQuicklist::elipsizeNoteTitle(Glib::ustring title)
{
    const int maxTitleLength = 20;

    //elipsize text
    if (title.size() > maxTitleLength)
    {
        title = title.substr(0, maxTitleLength);
        title += "...";
    }

    return "\"" + title + "\"";
}

void LauncherQuicklist::setMenuItemShowNote(Glib::ustring itemTitle)
{
    Glib::ustring label = lang::getString(lang::LAUNCHER_SHOW_NOTE);

    label += elipsizeNoteTitle(itemTitle);

    dbusmenu_menuitem_property_set(mitemShowNote, DBUSMENU_MENUITEM_PROP_LABEL, label.c_str());
}

void LauncherQuicklist::setMenuItemClearReminder(Glib::ustring itemTitle)
{
    Glib::ustring label = lang::getString(lang::LAUNCHER_CLEAR_REMINDER);

    label += elipsizeNoteTitle(itemTitle);

    dbusmenu_menuitem_property_set(mitemClearReminder, DBUSMENU_MENUITEM_PROP_LABEL, label.c_str());
}

void LauncherQuicklist::update(data::NoteInfoItemList& noteInfoList)
{
    uidCurrentReminder = 0;

    //always show new note item
    dbusmenu_menuitem_property_set_bool(mitemNewNote, DBUSMENU_MENUITEM_PROP_VISIBLE, true);

    //always hide show note item
    dbusmenu_menuitem_property_set_bool(mitemShowNote, DBUSMENU_MENUITEM_PROP_VISIBLE, false);

    //always hide clear reminder item
    dbusmenu_menuitem_property_set_bool(mitemClearReminder, DBUSMENU_MENUITEM_PROP_VISIBLE, false);

    //are there any new notifications?
    if (noteInfoList.size() > 0)
    {
        //then show clear reminder menu item with description
        NoteInfoItem& info = noteInfoList[0];

        //get first notification data
        note::ItemData item;
        if (MyAgendaApp::app->getDataManager().getNote(info.getUid(), item))
        {
            setMenuItemShowNote(item.getTitle());
            setMenuItemClearReminder(item.getTitle());

            dbusmenu_menuitem_property_set_bool(mitemShowNote, DBUSMENU_MENUITEM_PROP_VISIBLE, true);
            dbusmenu_menuitem_property_set_bool(mitemClearReminder, DBUSMENU_MENUITEM_PROP_VISIBLE, true);

            uidCurrentReminder = info.getUid();
        }
        else
        {
            std::cerr << "can't find note for quicklist menu item: " << info.getUid() << std::endl;
        }
    }
}
