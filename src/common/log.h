#pragma once
#include <string>
#include <iostream>

namespace fabula
{
	class Log
	{
	public:
		/* The severity of the message. */
		enum class Severity { High, Medium, Low };

		/* The type of message.
		 * Internal: Caused by incorrect usage of the API, or similar. 
		 * Verbose: Verbose logging of the application.
		 * External: Parse errors, etc. */
		enum class Type { Internal, Verbose, External };

		static Severity minimumSeverity;
		static bool logInternal, logVerbose, logExternal;

		static void e(const std::string& err, Severity sev, Type type)
		{
			if (shouldLog(sev, type))
				std::cerr << "Fabula error " << getInfoString(sev, type) << " : " << err << "\n";
		}

		static void w(const std::string& warn, Severity sev, Type type)
		{
			if (shouldLog(sev, type))
				std::cout << "Fabula warning " << getInfoString(sev, type) << " : " << warn << "\n";
		}

		static void l(const std::string& msg, Type type)
		{
			if (shouldLogType(type))
				std::clog << "Fabula:" << "[Type="<< getTypeString(type) << "] : " << msg << "\n";
		}

	private:

		static std::string getTypeString(Type type)
		{
			if (type == Type::Internal)
				return "Internal";
			else if (type == Type::External)
				return "External";
			else
				return "Verbose";
		}

		static std::string getSeverityString(Severity sev)
		{
			if (sev == Severity::High)
				return "High";
			else if (sev == Severity::Medium)
				return "Medium";
			else
				return "Low";
		}

		static std::string getInfoString(Severity sev, Type type)
		{
			return "[Severity="+getSeverityString(sev)+", Type="+getTypeString(type)+"]";
		}

		static bool shouldLogType(Type type)
		{
			switch (type)
			{
			case Type::External:
				if (!logExternal)
					return false;
			case Type::Internal:
				if (!logInternal)
					return false;
			case Type::Verbose:
				if (!logVerbose)
					return false;
			}
			return true;
		}

		static bool shouldLogSeverity(Severity sev)
		{
			switch (sev)
			{
			case Severity::Low:
				if (minimumSeverity != Severity::Low)
					return false;
				break;
			case Severity::Medium:
				if (minimumSeverity == Severity::High)
					return false;
				break;
			}

			return true;
		}

		static bool shouldLog(Severity sev, Type type)
		{
			return shouldLogType(type) && shouldLogSeverity(sev);
		}
	};
}