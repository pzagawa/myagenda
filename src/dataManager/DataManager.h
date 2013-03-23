/*
 * File:   DataManager.h
 * Author: piotr
 *
 * Created on July 1, 2012, 11:55 PM
 */

#pragma once

#include "SqlDatabase.h"
#include "SqlRecordSet.h"
#include "SqlTable.h"
#include "SqlField.h"
#include "NoteItemData.h"
#include "NoteInfoItem.h"
#include "NoteInfoSummary.h"
#include "DataTypes.h"
#include <vector>
#include <map>

class DataManager
{
private:
	//increase to trigger update process
	const static int DB_VERSION = 1;

private:
	static sql::Field notesTableNotesDefinition[];
	static sql::Field versionTableNotesDefinition[];

private:
	sql::Database db;
	sql::Table* notesTable;
	sql::Table* versionTable;

public:
	DataManager();
	virtual ~DataManager();

private:
	bool isDatabaseUpdate();
	void processDatabaseUpdate();
	void processDatabaseSetup();
	void addWelcomeNote();

public:
	void initialize(std::string fileName);

	bool getNote(long noteUid, note::ItemData& noteData);
	void addNote(note::ItemData noteData);
	bool updateNote(note::ItemData& noteData);
	bool deleteNote(long noteUid);

	void getNotesForDay(DateValue dateValue, data::NoteList& noteList);
	void getNotesForMonthView(DateValue dateBegin, DateValue dateEnd, data::NoteInfoSummaryMap& summaryMap);

	void getReminders(data::NoteInfoItemList& noteInfoList);

};
