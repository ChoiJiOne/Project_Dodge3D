#include "CommandLineUtils.h"

#include <array>
#include <algorithm>
#include <regex>

#include "Assertion.h"
#include "StringUtils.h"

bool bIsInitialized = false;
std::wstring executePath;
std::unordered_map<std::wstring, std::wstring> argumentMaps;

void CommandLineUtils::Parse()
{
	ASSERT(!bIsInitialized, "Parse method can only be called once after the program starts...");

	int32_t argc = __argc;
	wchar_t** argv = __wargv;

	executePath = argv[0];

	std::wregex pattern(L"^[^=]+=[^=]+$");
	for (std::size_t index = 1; index < argc; ++index)
	{
		if (std::regex_match(argv[index], pattern))
		{
			std::vector<std::wstring> keyValue = StringUtils::Split(argv[index], L"=");
			argumentMaps.insert({ keyValue.front(), keyValue.back() });
		}
	}

	bIsInitialized = true;
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

	std::wstring valueStr = StringUtils::ToLower(argumentMaps.at(key));
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

	return StringUtils::ToInt(argumentMaps.at(key), value);
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

	return StringUtils::ToFloat(argumentMaps.at(key), value);
}

bool CommandLineUtils::GetStringValue(const std::string& key, std::string& value)
{
	std::wstring convertKey = StringUtils::Convert(key);
	std::wstring convertValue;

	if (!GetStringValue(convertKey, convertValue))
	{
		return false;
	}

	value = StringUtils::Convert(convertValue);
	return true;
}

bool CommandLineUtils::GetStringValue(const std::string& key, std::wstring& value)
{
	std::wstring convertKey = StringUtils::Convert(key);
	return GetStringValue(convertKey, value);
}

bool CommandLineUtils::GetStringValue(const std::wstring& key, std::string& value)
{
	std::wstring convertValue;

	if (!GetStringValue(key, convertValue))
	{
		return false;
	}

	value = StringUtils::Convert(convertValue);
	return true;
}

bool CommandLineUtils::GetStringValue(const std::wstring& key, std::wstring& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	value = argumentMaps.at(key);
	return true;
}

std::wstring CommandLineUtils::GetExecutePath()
{
	return executePath;
}

bool CommandLineUtils::IsValid(const std::wstring& key)
{
	return argumentMaps.find(key) != argumentMaps.end();
}