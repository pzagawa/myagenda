/*
 * File:   DataTypes.h
 * Author: piotr
 *
 * Created on July 5, 2012, 10:15 PM
 */

#pragma once

#include "NoteItemData.h"
#include "NoteInfoItem.h"
#include "NoteInfoSummary.h"
#include <vector>
#include <map>

namespace data
{
	typedef std::vector<note::ItemData> NoteList;
	typedef std::map<long, NoteInfoSummary> NoteInfoSummaryMap;
	typedef std::vector<NoteInfoItem> NoteInfoItemList;

};
