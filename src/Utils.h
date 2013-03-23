/*
 * File:   Utils.h
 * Author: piotr
 *
 * Created on July 3, 2012, 20:43 PM
 */

#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

class utils
{
protected:
	static char* buffer;

public:
	static std::string numToString(long value);
	static std::string numToString(int value);

};

class RefGuard
{
private:
	int* refCounter;

public:
	RefGuard(int* refCounter)
	{
		this->refCounter = refCounter;

		int value = *this->refCounter;
		*this->refCounter = value + 1;
	}
	~RefGuard()
	{
		int value = *this->refCounter;
		*this->refCounter = value - 1;
	}
};
