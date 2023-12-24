#include "CommandLineUtils.h"

#include "Assertion.h"
#include "StringUtils.h"

#include <array>
#include <algorithm>
#include <regex>

bool CommandLineUtils::bIsInitialized_ = false;
std::unordered_map<std::wstring, std::wstring> CommandLineUtils::argumentMaps_;

void CommandLineUtils::Parse()
{
	ASSERT(!bIsInitialized_, "Parse method can only be called once after the program starts...");

	std::vector<std::wstring> arguments = StringUtils::Split(GetCommandLineW(), L" ");
	std::wregex pattern(L"^[^=]+=[^=]+$");
	for (std::size_t index = 1; index < arguments.size(); ++index)
	{
		if (std::regex_match(arguments[index], pattern))
		{
			std::vector<std::wstring> keyValue = StringUtils::Split(arguments[index], L"=");
			argumentMaps_.insert({ keyValue.front(), keyValue.back() });
		}
	}

	bIsInitialized_ = true;
}