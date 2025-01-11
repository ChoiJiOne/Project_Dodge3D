#pragma once

#include <string>

/**
 * ����� â�� �����õ� ���ڿ��� ����մϴ�.
 * �̶�, �� ����� DEBUG_MODE�� RELWITHDEBINFO_MODE ���� �����մϴ�.
 */
void DebugPrintF(const char* format, ...);

/** ǥ�� ���ڿ� ����� ���ڿ� �������� �����մϴ�. */
std::string PrintF(const char* format, ...);

/** ǥ�� ���ڿ� ����� ���ڿ� �������� �����մϴ�. */
std::wstring PrintF(const wchar_t* format, ...);