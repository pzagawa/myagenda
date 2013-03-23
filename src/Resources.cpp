/*
 * File:   Resources.cpp
 * Author: piotr
 *
 * Created on June 26, 2012, 10:20 PM
 */

#include "Resources.h"

Resources* Resources::res = NULL;

Resources::Resources(Glib::RefPtr<Gtk::Builder> ui)
{
    res = this;

    this->ui = ui;
}

Resources::~Resources()
{
}

void Resources::initialize()
{
	app_name = "MyAgenda";
	app_author = "Piotr Zagawa";
	app_version ="1.2";

    ui->get_widget("imgReminderIcon", imgReminderIcon);
    ui->get_widget("imgReminderOnIcon", imgReminderOnIcon);
    ui->get_widget("imgBtnEdit", imgBtnEdit);
    ui->get_widget("imgBtnDelete", imgBtnDelete);
    ui->get_widget("imgBtnAbout", imgBtnAbout);
    ui->get_widget("imgBtnNewNote", imgBtnNewNote);

    fontName = "Ubuntu";
}
