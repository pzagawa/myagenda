/*
 * File:   NoteItemView.h
 * Author: piotr
 *
 * Created on June 25, 2012, 8:45 PM
 */

#pragma once

#include <gtkmm.h>
#include "NoteItemData.h"

namespace note
{

class ItemView
	: public Gtk::DrawingArea
{
public:
	const static int BUTTON_ID_EDIT = 1;
	const static int BUTTON_ID_DELETE = 2;
	const static int BUTTON_ID_TOGGLE_NOTIFICATION = 3;

private:
	const static int FONT_SIZE = 14;
	const static int FONT_SIZE_SMALL = 10;
	const static int HEIGHT = 68;
	const static int TIME_WIDTH = 70;
	const static int PADDING = 4;
	const static int SPACE = 2;
	const static int BTN_WIDTH = 32;

private:
	enum ColorMode
	{
		COLOR_INACTIVE,
		COLOR_OK,
		COLOR_ALARM,
	};

private:
	ItemData data;
	bool _isSelected;

	Gdk::Rectangle rectTime;
	Gdk::Rectangle rectTitle;
	Gdk::Rectangle rectDescription;

	Gdk::Rectangle rectBtnEdit;
	Gdk::Rectangle rectBtnDelete;
	Gdk::Rectangle rectClearNotification;

    Pango::FontDescription fontTime;
    Pango::FontDescription fontTitle;
    Pango::FontDescription fontDescription;

public:
	sigc::signal<void, ItemView*> signal_item_selected;
	sigc::signal<void, ItemView*, int> signal_item_button_clicked;

public:
	ItemView();
	virtual ~ItemView();

protected:
	virtual void on_realize();
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual bool on_button_release_event(GdkEventButton* event);

private:
	bool isHit(GdkEventButton* event, Gdk::Rectangle& rect)	;
	int getAllButtonsWidth();
	void updateButtonsLayout(const int width, const int height, const int containerTop, const int containerHeight);
	void updateClearNotificationButtonLayout(const int width, const int height);
	void drawInnerShadow(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawBackground(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawTime(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawTitle(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawDescription(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawReminderIcon(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawButtons(const Cairo::RefPtr<Cairo::Context>& cr, const int width, const int height);
	void drawButton(const Cairo::RefPtr<Cairo::Context>& cr, Gtk::Image* image, Gdk::Rectangle rect);
	ColorMode getColorMode();

public:
	void setData(ItemData data);
	ItemData& getData();
	void setSelected(bool value);
	bool isSelected();

};

//note
};
