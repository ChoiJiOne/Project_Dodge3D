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

bool CommandLineUtils::GetBoolValue(const std::string& key, bool& value)
{
	std::wstring convertKey = StringUtils::Convert(key);
	return GetBoolValue(convertKey, value);
}

bool CommandLineUtils::GetBoolValue(const std::wstring& key, bool& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	std::wstring valueStr = StringUtils::ToLower(argumentMaps_.at(key));
	if (valueStr == L"true")
	{
		value = true;
		return true;

	}
	else if (valueStr == L"false")
	{
		value = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool CommandLineUtils::GetIntValue(const std::string& key, int32_t& value)
{
	std::wstring convertKey = StringUtils::Convert(key);
	return GetIntValue(convertKey, value);
}

bool CommandLineUtils::GetIntValue(const std::wstring& key, int32_t& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	return StringUtils::ToInt(argumentMaps_.at(key), value);
}

bool CommandLineUtils::GetFloatValue(const std::string& key, float& value)
{
	std::wstring convertKey = StringUtils::Convert(key);
	return GetFloatValue(convertKey, value);
}

bool CommandLineUtils::GetFloatValue(const std::wstring& key, float& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	return StringUtils::ToFloat(argumentMaps_.at(key), value);
}

bool CommandLineUtils::IsValid(const std::wstring& key)
{
	return argumentMaps_.find(key) != argumentMaps_.end();
}
