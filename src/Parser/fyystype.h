#pragma once
#include "parse_nodes.h"
struct FYYSType
{
    std::string stdstring;
    fabula::parsing::node::Header header;
    fabula::parsing::node::Destination destination;
    fabula::parsing::node::Choice choice;
    fabula::parsing::node::Scene scene;
    fabula::parsing::node::Section section;
    fabula::parsing::node::String fstring;
    std::vector<std::shared_ptr<fabula::parsing::node::Choice>> choicelist;
    int integer;

    FYYSType(){}
    FYYSType(const char* str) : stdstring(str) {}
};
