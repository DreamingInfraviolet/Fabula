#pragma once

/**
* @author Anima Seteine
* @purpose Provides misc utility functions.
*/

#include<sstream>
#include<string>

template<class T>
static std::string toString(const T& t)
{
    std::ostringstream str;
    str << t;
    return str.str();
}