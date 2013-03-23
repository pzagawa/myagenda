/*
 * File:   NotificationManager.cpp
 * Author: piotr
 *
 * Created on July 9, 2012, 10:43 PM
 */

#include "NotificationManager.h"
#include "MyAgendaApp.h"
#include "Lang.h"
#include "Preferences.h"

NotificationManager::NotificationManager()
{
    //get unity launcher
    unityLauncher = unity_launcher_entry_get_for_desktop_id("myagenda.desktop");
}

NotificationManager::NotificationManager(const NotificationManager& orig)
{
}

NotificationManager::~NotificationManager()
{
}

int NotificationManager::getRemindersCountForToday(data::NoteInfoItemList& noteInfoList)
{
   const long nowTime = DateValue::now().getHashCode();

    int count = 0;

    for (int index = 0; index < noteInfoList.size(); index++)
    {
        NoteInfoItem& info = noteInfoList[index];
        if (info.getDate() == nowTime)
            count++;
    }

    return count;
}

void NotificationManager::showNotification(std::string title, std::string text)
{
    if (!hasNotificationTextChanged(title, text))
        return;

    text = Resources::res->app_name + "\n" + text;

    if (notify_init(Resources::res->app_name.c_str()))
    {
        NotifyNotification* notification = notify_notification_new(title.c_str(), text.c_str(), MyAgendaApp::app->getAppIconFileNamePath().c_str());

        GError* error = NULL;
        if (!notify_notification_show(notification, &error))
        {
            std::cerr << "Can't show notification: " << text << std::endl;
        }

        notify_uninit();
    }
}

//how much time to wait if no text change to show the same notification again
int NotificationManager::getUpdateTimeoutSeconds()
{
    return (60 * Preferences::prefs->getNotificationExpirationMinutes());
}

bool NotificationManager::hasNotificationTextChanged(std::string title, std::string text)
{
    static std::string SHA;
    static Glib::TimeVal lastUpdateTime;

    std::string currentSHA = sql::generateSHA(title + text);

    //check if notification text has changed
    if (SHA != currentSHA)
    {
        lastUpdateTime.assign_current_time();
        lastUpdateTime.add_seconds(getUpdateTimeoutSeconds());

        SHA = currentSHA;
        return true;
    }

    //when notification text not changed, check timeout
    Glib::TimeVal currentTime;
    currentTime.assign_current_time();

    if (currentTime.as_double() > lastUpdateTime.as_double())
    {
        lastUpdateTime.assign_current_time();
        lastUpdateTime.add_seconds(getUpdateTimeoutSeconds());

        SHA = currentSHA;
        return true;
    }

    return false;
}

bool NotificationManager::createNotificationText(data::NoteInfoItemList& noteInfoList, std::string& title, std::string& text)
{
    if (noteInfoList.size() > 0)
    {
        NoteInfoItem& info = noteInfoList[0];

        note::ItemData item;
        if (MyAgendaApp::app->getDataManager().getNote(info.getUid(), item))
        {
            title = item.getTitle();

            const int todayCount = getRemindersCountForToday(noteInfoList);
            const int othersCount = noteInfoList.size() - todayCount;

            text = lang::getNotificationString(todayCount, othersCount);

            return true;
        }
    }

    return false;
}

void NotificationManager::updateUnityLauncher(int count)
{
    if (count == 0)
    {
        unity_launcher_entry_set_count_visible(unityLauncher, false);
    }
    else
    {
        unity_launcher_entry_set_count_visible(unityLauncher, true);
        unity_launcher_entry_set_count(unityLauncher, count);
    }
}

void NotificationManager::updateUnityNotifications(data::NoteInfoItemList& noteInfoList)
{
    //handle unity launcher icon information
    updateUnityLauncher(noteInfoList.size());

    //handle notification message
    std::string ntTitle;
    std::string ntText;

    if (createNotificationText(noteInfoList, ntTitle, ntText))
    {
        showNotification(ntTitle, ntText);
    }
}
