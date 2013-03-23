/*
 * File:   NoteListView.h
 * Author: piotr
 *
 * Created on June 25, 2012, 9:01 PM
 */

#pragma once

#include <gtkmm.h>
#include "NoteItemView.h"
#include "NoteItemData.h"

namespace note
{

class ListView
	: public Gtk::Box
{
private:
	Glib::RefPtr<Gtk::Builder> ui;
	std::vector<ItemView*> views;

	long lastSelectedItemUid;

public:
	sigc::signal<void, long, int> signal_item_button_clicked;

public:
	ListView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ListView();

private:
	virtual void on_realize();
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

	void OnListItemSelected(ItemView* itemView);
	void OnListItemButtonClicked(ItemView* itemView, int buttonId);

public:
	void addItem(ItemData& data);
	void clear();
	int getCount();
	void clearSelection();
	void restoreSelection();

};

//note
};
