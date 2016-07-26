#pragma once
#include "parse_exception.h"
#include <map>
#include <iostream>

class CmdHelper
{
    int argc;
    char** argv;

public:
    CmdHelper(int argc_, char** argv_)
        : argc(argc_), argv(argv_)
	{
		establishParseRules();
		std::string error;
		if ((error = parseArgs()) != "")
			throw new std::runtime_error(std::string("Unable to parse arguments: ") + error);
	}

    virtual void usage() = 0;
	const char* programName() { return argv[0]; }

protected:
	std::map<std::string,  std::pair<int, bool>> mRules;
	virtual void establishParseRules() = 0;
	virtual std::string parseArgs() = 0;
};

class HtmlInterfaceCmdHelper : public CmdHelper
{
public:
    virtual void usage() override
    {
		std::cout << "Fabula HTML Generator Interface\n"
			"Usage: " << programName() << " [options]\n"
			"Options:\n"
			"-f <arg>         Specifies the source .fab file to read. \n"
			"-t <arg>         Specifies the template html file to use.\n"
			"--help           Provides additional help information.\n"
			"-v | --verbose   Provides additional internal messages.\n"
			"-m               Mercilessly returns an error code, even on warnings.\n"
			"-p <arg>         Specifies a prefix to be appended to each output filename.\n";
    }

protected:
	virtual void establishParseRules() override
	{
		mRules =
		{
			{"-f", {0, true}},
			{"-t", {1, true}},
			{"--help", {2, false}},
			{ "-v", {3, false}},
			{ "-verbose", {3, false}},
			{ "-m", {4, false}},
			{ "-p", {5, true}}
		};
	}

	virtual std::string parseArgs() override
	{

	}
};
