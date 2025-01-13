#pragma once

#include "Utils/Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * �� ��ũ�δ� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * ex)
 * A* a = Something();
 * CHECK(a != nullptr);
 */
#ifndef CHECK
#define CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		__debugbreak();\
	}\
}
#endif
/**
 * �� ��ũ�δ� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * ex)
 * A* a = Something();
 * ASSERT(a != nullptr, "Failed to create A object in %s", "example");
 */
#ifndef ASSERT
#define ASSERT(EXP, ...)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n> Description: ", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF(__VA_ARGS__);\
		DebugPrintF("\n\n");\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
#ifndef CHECK
#define CHECK(EXP) (void)(EXP)
#endif
#ifndef ASSERT
#define ASSERT(EXP, ...) (void)(EXP)
#endif
#endif