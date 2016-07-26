#include "log.h"

namespace fabula
{
	Log::Severity Log::minimumSeverity = Log::Severity::Low;
	bool Log::logInternal = true, Log::logVerbose = true, Log::logExternal = true;
}