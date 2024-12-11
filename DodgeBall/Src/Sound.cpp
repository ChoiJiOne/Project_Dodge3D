#include "Sound.h"

#include "Assertion.h"
#include "AudioManager.h"
#include "MathUtils.h"

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

void Sound::SetVolume(float volume)
{
	volume = MathUtils::Clamp<float>(volume, 0.0f, 1.0f);
	ma_sound_set_volume(sound_.get(), volume);
}

float Sound::GetVolume()
{
	return ma_sound_get_volume(sound_.get());
}

void Sound::SetLooping(bool bIsLoop)
{
	ma_sound_set_looping(sound_.get(), static_cast<ma_bool32>(bIsLoop));
}

bool Sound::IsLooping()
{
	return ma_sound_is_looping(sound_.get()) == MA_TRUE;
}

void Sound::Play()
{
	ma_sound_start(sound_.get());
}

bool Sound::IsPlaying()
{
	return ma_sound_is_playing(sound_.get()) == MA_TRUE;
}

bool Sound::IsDone()
{
	return ma_sound_at_end(sound_.get()) == MA_TRUE;
}

void Sound::Stop()
{
	ma_sound_stop(sound_.get());
}

bool Sound::IsStopping()
{
	return !IsDone() && !IsPlaying();
}

void Sound::Reset()
{
	ma_sound_seek_to_pcm_frame(sound_.get(), 0);
}