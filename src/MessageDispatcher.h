/*
 * File:   MyAgendaApp.h
 * Author: piotr
 *
 * Created on August 7, 2012, 11:32 PM
 */

#pragma once

class MessageDispatcher
{
public:
	static const int NEW_NOTE = 1;
	static const int SHOW_NOTE = 2;
	static const int CLEAR_REMINDER = 3;

public:
	virtual void updateTarget(int message_id, void* data) = 0;

};
