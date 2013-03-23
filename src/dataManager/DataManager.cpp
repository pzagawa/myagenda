/*
 * File:   DataManager.cpp
 * Author: piotr
 *
 * Created on July 1, 2012, 11:55 PM
 */

#include "DataManager.h"
#include "Utils.h"
#include "Lang.h"
#include <algorithm>

sql::Field DataManager::notesTableNotesDefinition[] =
{
    sql::Field(sql::FIELD_KEY),
    sql::Field("date", sql::type_int, sql::flag_not_null),
    sql::Field("time", sql::type_int, sql::flag_not_null),
    sql::Field("isReminder", sql::type_bool, sql::flag_not_null),
    sql::Field("isNotificationCleared", sql::type_bool, sql::flag_not_null),
    sql::Field("title", sql::type_text, sql::flag_not_null),
    sql::Field("details", sql::type_text),
    sql::Field(sql::DEFINITION_END),
};

sql::Field DataManager::versionTableNotesDefinition[] =
{
    sql::Field(sql::FIELD_KEY),
    sql::Field("version", sql::type_int, sql::flag_not_null),
    sql::Field(sql::DEFINITION_END),
};

DataManager::DataManager()
{
    this->notesTable = NULL;
    this->versionTable = NULL;
}

DataManager::~DataManager()
{
    if (notesTable)
        delete notesTable;
    if (versionTable)
        delete versionTable;
}

void DataManager::initialize(std::string fileName)
{
    try
	{
		db.open(fileName);

        notesTable = new sql::Table(db.getHandle(), "notes", &notesTableNotesDefinition[0]);

        const bool notesTableCreated = !notesTable->exists();

		notesTable->create();

        versionTable = new sql::Table(db.getHandle(), "version", &versionTableNotesDefinition[0]);
		versionTable->create();

        if (isDatabaseUpdate())
            processDatabaseUpdate();

        if (notesTableCreated)
            processDatabaseSetup();
	}
    catch (sql::Exception e)
    {
        std::cerr << "database initialize error: " + e.msg() << std::endl;
	}
}

bool DataManager::isDatabaseUpdate()
{
    versionTable->open();

    if (versionTable->recordCount() == 0)
    {
        sql::Record r(versionTable->fields());
        r.setInteger("version", DB_VERSION);
        versionTable->addRecord(&r);
        return true;
    }

    if (sql::Record* r = versionTable->getTopRecord())
    {
        const int lastVersion = r->getValue("version")->asInteger();

        if (lastVersion < DB_VERSION)
        {
            r->setInteger("version", DB_VERSION);
            versionTable->updateRecord(r);
            return true;
        }
    }

    return false;
}

void DataManager::processDatabaseUpdate()
{
    //TODO: for future releases if db version change

}

void DataManager::processDatabaseSetup()
{
    addWelcomeNote();
}

void DataManager::addWelcomeNote()
{
    note::ItemData noteData;

    noteData.setDate(DateValue::now());
    noteData.setTime(TimeValue::now());
    noteData.setReminder(true);
    
    noteData.setTitle(lang::getString(lang::WELCOME_NOTE_TITLE));
    noteData.setDetails(lang::getString(lang::WELCOME_NOTE_DETAILS));

    addNote(noteData);
}

void DataManager::addNote(note::ItemData noteData)
{
    try
	{
        sql::Record record(notesTable->fields());
        noteData.setRecord(record);
        notesTable->addRecord(&record);
	}
    catch (sql::Exception e)
    {
        std::cerr << "note insert error: " + e.msg() << std::endl;
	}
}

bool DataManager::getNote(long noteUid, note::ItemData& noteData)
{
    notesTable->getRecordByKeyId(noteUid);

    if (sql::Record* record = notesTable->getTopRecord())
    {
        noteData.parseRecord(*record);
        return true;
    }

    return false;
}

bool DataManager::updateNote(note::ItemData& noteData)
{
    notesTable->getRecordByKeyId(noteData.getUid());

    if (sql::Record* record = notesTable->getTopRecord())
    {
        noteData.setRecord(*record);
        notesTable->updateRecord(record);
    }

    return false;
}

bool DataManager::deleteNote(long noteUid)
{
    std::string where = "_ID == " + utils::numToString(noteUid);
    return notesTable->deleteRecords(where);
}

void DataManager::getNotesForDay(DateValue dateValue, data::NoteList& noteList)
{
    const long timeNow = DateTimeValue::now().getHashCode();

    noteList.clear();

    std::string where = "date = ";
        where += dateValue.getHashCodeText();

    notesTable->open(where, "time asc, title asc");

    for (int index = 0; index < notesTable->recordCount(); index++)
    {
        if (sql::Record* record = notesTable->getRecord(index))
        {
            note::ItemData noteData;
            noteData.parseRecord(*record);

            if (timeNow >= noteData.getDateTime())
                noteData.setNotification(true);

            noteList.push_back(noteData);
        }
    }
}

void DataManager::getNotesForMonthView(DateValue dateBegin, DateValue dateEnd, data::NoteInfoSummaryMap& summaryMap)
{
    const long timeNow = DateTimeValue::now().getHashCode();

    summaryMap.clear();

    NoteInfoItem infoItem;

    std::string query = "select _ID, date, time, isReminder, isNotificationCleared";
        query += " from " + notesTable->name();
        query += " where date >= " + dateBegin.getHashCodeText() + " and date <= " + dateEnd.getHashCodeText();

    notesTable->query(query);

    for (int index = 0; index < notesTable->recordCount(); index++)
    {
        if (sql::Record* record = notesTable->getRecord(index))
        {
            infoItem.parseRecord(*record);

            const long dateKey = infoItem.getDate();
            NoteInfoSummary& daySummary = summaryMap[dateKey];

            daySummary.aggregate(infoItem, timeNow);
        }
    }
}

struct CompareNoteInfoItem :
    public std::binary_function<NoteInfoItem,NoteInfoItem, bool>
{
    inline bool operator()(const NoteInfoItem& a, const NoteInfoItem& b)
    {
        return a.getDateTime() > b.getDateTime();
    }
};

void DataManager::getReminders(data::NoteInfoItemList& noteInfoList)
{
    const long timeNow = DateTimeValue::now().getHashCode();

    const std::string dateNowText = DateValue::now().getHashCodeText();

    std::string query = "select _ID, date, time, isReminder, isNotificationCleared";
        query += " from " + notesTable->name();
        query += " where isReminder = 1 and isNotificationCleared = 0";
        query += " and date <= " + dateNowText;

    notesTable->query(query);

    noteInfoList.clear();

    NoteInfoItem infoItem;

    for (int index = 0; index < notesTable->recordCount(); index++)
    {
        if (sql::Record* record = notesTable->getRecord(index))
        {
            infoItem.parseRecord(*record);

            if (timeNow >= infoItem.getDateTime())
            {
                noteInfoList.push_back(infoItem);
            }
        }
    }

    //sort items by real time order. Newest items first
    std::sort(noteInfoList.begin(), noteInfoList.end(), CompareNoteInfoItem());
}
