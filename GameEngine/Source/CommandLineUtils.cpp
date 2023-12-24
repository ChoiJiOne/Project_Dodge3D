#include "CommandLineUtils.h"

#include "Assertion.h"
#include "StringUtils.h"

#include <array>
#include <algorithm>
#include <regex>

bool CommandLineUtils::bIsInitialized_ = false;

void CommandLineUtils::Parse(const wchar_t* commandLine)
{
	ASSERT(!bIsInitialized_, "Parse method can only be called once after the program starts...");

	bIsInitialized_ = true;
}
