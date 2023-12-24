#include "CommandLineUtils.h"

#include "Assertion.h"
#include "StringUtils.h"

#include <array>
#include <algorithm>
#include <regex>

bool CommandLineUtils::bIsInitialized_ = false;
std::unordered_map<std::wstring, std::wstring> CommandLineUtils::argumentMaps_;

void CommandLineUtils::Parse(const wchar_t* commandLine)
{
	ASSERT(!bIsInitialized_, "Parse method can only be called once after the program starts...");

	std::vector<std::wstring> arguments = StringUtils::Split(commandLine, L" ");
	
	std::wregex pattern(L"^[^=]+=[^=]+$");
	for (std::size_t index = 0; index < arguments.size(); ++index)
	{
		if (std::regex_match(arguments[index], pattern))
		{
			std::vector<std::wstring> keyValue = StringUtils::Split(arguments[index], L"=");
			argumentMaps_.insert({ keyValue.front(), keyValue.back() });
		}
	}

	bIsInitialized_ = true;
}

void CommandLineUtils::ParseArguments(const std::vector<std::wstring>& arguments)
{
	ASSERT(!bIsInitialized_, "Parse method can only be called once after the program starts...");

	std::wregex pattern(L"^[^=]+=[^=]+$");
	for (std::size_t index = 0; index < arguments.size(); ++index)
	{
		if (std::regex_match(arguments[index], pattern))
		{
			std::vector<std::wstring> keyValue = StringUtils::Split(arguments[index], L"=");
			argumentMaps_.insert({ keyValue.front(), keyValue.back() });
		}
	}

	bIsInitialized_ = true;
}
