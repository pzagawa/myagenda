/*
 * File:   NoteListView.cpp
 * Author: piotr
 *
 * Created on June 25, 2012, 9:01 PM
 */

#include "NoteListView.h"
#include <iostream>

namespace note
{

ListView::ListView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Box(cobject), ui(refGlade)
{
    lastSelectedItemUid = 0;
}

ListView::~ListView()
{
}

void ListView::on_realize()
{
    Gtk::Widget::on_realize();

}

bool ListView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();

    const int width = allocation.get_width();
    const int height = allocation.get_height();

    return true;
}

int ListView::getCount()
{
    return get_children().size();
}

void ListView::clear()
{
    for (int index = 0; index < views.size(); index++)
    {
        ItemView* item = views[index];
        remove(*item);
        delete item;
    }

    views.clear();
}

void ListView::addItem(ItemData& data)
{
    ItemView* itemView = new ItemView();

    itemView->setData(data);

    itemView->signal_item_selected.connect(sigc::mem_fun(this, &ListView::OnListItemSelected));
    itemView->signal_item_button_clicked.connect(sigc::mem_fun(this, &ListView::OnListItemButtonClicked));

    views.push_back(itemView);

    pack_start(*itemView);

    itemView->show();
}

void ListView::restoreSelection()
{
    if (lastSelectedItemUid != 0)
    {
        clearSelection();

        //restore selection to previously selected item after list has been reloaded
        for (int index = 0; index < views.size(); index++)
        {
            ItemView* item = views[index];
            if (item->getData().getUid() == lastSelectedItemUid)
                item->setSelected(true);
        }
    }
}

void ListView::clearSelection()
{
    for (int index = 0; index < views.size(); index++)
    {
        ItemView* item = views[index];
        if (item->isSelected())
            item->setSelected(false);
    }
}

void ListView::OnListItemSelected(ItemView* itemView)
{
    const bool wasSelected = itemView->isSelected();

    clearSelection();

    itemView->setSelected(!wasSelected);

    if (itemView->isSelected())
    {
        ItemData& data = itemView->getData();

        //save last selected item uid
        lastSelectedItemUid = data.getUid();

        return;
    }

    //reset last selected item uid
    lastSelectedItemUid = 0;
}

void ListView::OnListItemButtonClicked(ItemView* itemView, int buttonId)
{
    ItemData& data = itemView->getData();
    signal_item_button_clicked.emit(data.getUid(), buttonId);
}

//note
};
