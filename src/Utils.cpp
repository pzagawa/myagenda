/*
 * File:   Utils.h
 * Author: piotr
 *
 * Created on July 3, 2012, 20:43 PM
 */

#include "Utils.h"

char* utils::buffer = new char[256];

std::string utils::numToString(long value)
{
    std::sprintf(buffer, "%ld", value);
    return buffer;
};

std::string utils::numToString(int value)
{
    std::sprintf(buffer, "%d", value);
    return buffer;
};
