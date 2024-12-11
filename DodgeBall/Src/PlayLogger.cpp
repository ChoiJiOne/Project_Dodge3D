#include "PlayLogger.h"

#include <algorithm>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileUtils.h"
#include "IApplication.h"
#include "StringUtils.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "TTFont.h"
#include "Window.h"

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

	logFilePath_ = L"Resource/Bin/Rank.bin";
	if (FileUtils::IsValidPath(logFilePath_))
	{
		ReadLogFile();
	}

	font32_ = ResourceManager::Get().GetResource<TTFont>("Font32");
	font64_ = ResourceManager::Get().GetResource<TTFont>("Font64");

	int32_t width;
	int32_t height;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(width, height);

	rankCenter_ = Vector2f(static_cast<float>(width) / 2.0f, 200.0f);
	rankColor_ = Vector4f(1.0f, 0.5f, 0.1f, 1.0f);

	logCenter_ = Vector2f(static_cast<float>(width) / 2.0f, 250.0f);
	logColor_ = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	logRecentColor_ = Vector4f(1.0f, 0.3f, 0.3f, 1.0f);
	logStride_ = 40.0f;

	maxLogCount_ = 5;

	bIsInitialized_ = true;
}

void PlayLogger::Tick(float deltaSeconds)
{
}

void PlayLogger::Render()
{
	RenderManager::Get().RenderText2D(font64_, L"Rank", rankCenter_, Vector4f(1.0f, 1.0f, 1.0f, 1.0f));

	Vector2f center = logCenter_;
	for (std::size_t index = 0; index < playLog_.size() && index < maxLogCount_; ++index)
	{
		Vector4f color = (playLog_[index].day == recentPlayLog.day && playLog_[index].time == recentPlayLog.time) ? logRecentColor_ : logColor_;
		std::wstring logText = StringUtils::PrintF(L"%19s %3d", playLog_[index].day.c_str(), static_cast<int32_t>(playLog_[index].time));
		
		RenderManager::Get().RenderText2D(font32_, logText, center, color);

		center.y += logStride_;
	}
}

void PlayLogger::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	WriteLogFile();

	bIsInitialized_ = false;
}

void PlayLogger::RecordPlayLog(const std::wstring& day, const float& time)
{
	recentPlayLog = PlayLog{ day, time };
	playLog_.push_back(recentPlayLog);

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
	std::vector<uint8_t> buffer = FileUtils::ReadBufferFromFile(logFilePath_);
	uint32_t countChunk = static_cast<uint32_t>(buffer.size()) / static_cast<uint32_t>(sizeof(PlayLogChunk));

	PlayLogChunk* chunkBufferPtr = reinterpret_cast<PlayLogChunk*>(buffer.data());
	for (uint32_t index = 0; index < countChunk; ++index)
	{
		std::wstring day(chunkBufferPtr[index].day, chunkBufferPtr[index].day + MAX_LOG_SIZE);
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
	
	std::wstring basePath = FileUtils::GetBasePath(logFilePath_);
	if (!FileUtils::IsValidPath(basePath))
	{
		FileUtils::MakeDirectory(basePath);
	}

	FileUtils::WriteBufferToFile(logFilePath_, buffer);
}