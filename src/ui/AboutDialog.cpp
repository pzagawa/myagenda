/*
 * File:   AboutDialog.h
 * Author: piotr
 *
 * Created on July 7, 2012, 20:36 PM
 */

#include <iostream>
#include "AboutDialog.h"
#include "Lang.h"
#include "MyAgendaApp.h"

AboutDialog::AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::AboutDialog(cobject), ui(refGlade)
{
}

AboutDialog::~AboutDialog()
{
}

int AboutDialog::create(Gtk::Window& parent)
{
    AboutDialog* dialog = NULL;

    //load and create dialog
    const Glib::RefPtr<Gtk::Builder> ui = MyAgendaApp::app->getUiBuilder();
    const std::string& fileName = MyAgendaApp::app->getUiFileNamePath();

    try
    {
        Glib::RefPtr<Gtk::Builder> uiDialog = ui->create_from_file(fileName,"dlgAbout");
        uiDialog->get_widget_derived("dlgAbout", dialog);
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    //show and get result
    const int response = dialog->run();

    dialog->hide();
    delete dialog;

    return response;
}

void AboutDialog::on_realize()
{
    Gtk::AboutDialog::on_realize();

    this->set_version(Resources::res->app_version);
}
