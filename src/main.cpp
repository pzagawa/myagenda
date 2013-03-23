/*
 * File:   main.cpp
 * Author: piotr
 *
 * Created on June 20, 2012, 7:24 PM
 */

#include "MyAgendaApp.h"
#include "MainWindow.h"
#include "Resources.h"
#include <iostream>
#include <sysexits.h>

using namespace std;

const int EX_INSTANCE_RUNNING = 1;

int main(int argc, char** argv)
{
    MyAgendaApp myAgendaApp(argc, argv);

    if (myAgendaApp.isAlreadyRunning())
    {
        std::cerr << "instance already running" << std::endl;

        myAgendaApp.activate();

        return EX_INSTANCE_RUNNING;
    }

    myAgendaApp.initialize();
    myAgendaApp.loadUi();

    Resources resources(myAgendaApp.getUiBuilder());
    resources.initialize();

    MainWindow* mainWindow = MainWindow::get(myAgendaApp.getUiBuilder());

    myAgendaApp.addMessageTarget(mainWindow);
    
    myAgendaApp.run(*mainWindow);

    return EX_OK;
}
