#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	Mix_AllocateChannels(512);
}

bool SoundManager::load(const std::string& file_name, const std::string& id, const sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		const auto pMusic = Mix_LoadMUS(file_name.c_str());

		if (pMusic == nullptr)
		{
			std::cout << "Could not load music: ERROR - "
				<< Mix_GetError() << std::endl;
			return false;
		}

		m_music[id] = pMusic;
		return true;
	}
	if (type == SOUND_SFX)
	{
		const auto pChunk = Mix_LoadWAV(file_name.c_str());
		
		if (pChunk == nullptr)
		{
			std::cout << "Could not load SFX: ERROR - "
				<< Mix_GetError() << std::endl;
		
			return false;
		}
		
		m_sfxs[id] = pChunk;
		return true;
	}

	return false;
}

void SoundManager::playMusic(const std::string& id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}


void SoundManager::playSound(int const channel, std::string id, int loop)
{
	Mix_PlayChannel(channel, m_sfxs[id], loop);
}

void SoundManager::stopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::stopSound(int const channel)
{
	Mix_HaltChannel(channel);
}

bool SoundManager::isSoundPlaying(int const channel) const
{
	return Mix_Playing(channel);
}

void SoundManager::init()
{

}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

void SoundManager::clean()
{

}

