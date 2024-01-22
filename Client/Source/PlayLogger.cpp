#include "PlayLogger.h"

#include <algorithm>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "RenderManager.h"
#include "TTFont.h"

PlayLogger::~PlayLogger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PlayLogger::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize play logger object...");

	std::wstring rootPath;
	ASSERT(CommandLineUtils::GetStringValue("rootPath", rootPath), "failed to get root path in command line...");

	logFilePath_ = rootPath + L"Client/Resource/PlayLog.log";
	if (FileUtils::IsValidPath(logFilePath_))
	{
		ReadLogFile();
	}

	bIsInitialized_ = true;
}

void PlayLogger::Tick(float deltaSeconds)
{
}

void PlayLogger::Render()
{
}

void PlayLogger::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	WriteLogFile();

	bIsInitialized_ = false;
}

void PlayLogger::RecordPlayLog(const std::wstring& day, const float& time)
{
	playLog_.push_back({ StringUtils::Convert(day), time });

	auto recordSortFunc = [](const PlayLog& left, const PlayLog& right)
	{
		if (left.time > right.time)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	std::sort(playLog_.begin(), playLog_.end(), recordSortFunc);
}

void PlayLogger::ReadLogFile()
{
	std::vector<uint8_t> buffer = FileUtils::ReadBufferFromFile(logFilePath_);\
	uint32_t countChunk = static_cast<uint32_t>(buffer.size()) / static_cast<uint32_t>(sizeof(PlayLogChunk));

	PlayLogChunk* chunkBufferPtr = reinterpret_cast<PlayLogChunk*>(buffer.data());
	for (uint32_t index = 0; index < countChunk; ++index)
	{
		std::string day(chunkBufferPtr[index].day, chunkBufferPtr[index].day + MAX_LOG_SIZE);
		float time = chunkBufferPtr[index].time;

		playLog_.push_back({ day, time });
	}
}

void PlayLogger::WriteLogFile()
{
	uint32_t bufferSize = static_cast<uint32_t>(sizeof(PlayLogChunk)) * static_cast<uint32_t>(playLog_.size());
	std::vector<uint8_t> buffer(bufferSize);

	PlayLogChunk* chunkBufferPtr = reinterpret_cast<PlayLogChunk*>(buffer.data());
	for (uint32_t index = 0; index < playLog_.size(); ++index)
	{
		std::copy(playLog_[index].day.begin(), playLog_[index].day.end(), chunkBufferPtr[index].day);
		chunkBufferPtr[index].time = playLog_[index].time;
	}
	
	FileUtils::WriteBufferToFile(logFilePath_, buffer);
}