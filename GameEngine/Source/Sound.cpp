#include "Sound.h"

#include "Assertion.h"
#include "AudioManager.h"

Sound::~Sound()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Sound::Initialize(const std::wstring& path)
{
	ASSERT(!bIsInitialized_, "already initialize sound resource...");

	sound_ = std::make_unique<ma_sound>();
	ASSERT(ma_sound_init_from_file_w(AudioManager::Get().GetAudioEngine(), path.c_str(), 0, nullptr, nullptr, sound_.get()) == MA_SUCCESS, L"failed to initialize sound from %s file...", path.c_str());

	bIsInitialized_ = true;
}

void Sound::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	ma_sound_uninit(sound_.get());
	sound_.reset();

	bIsInitialized_ = false;
}