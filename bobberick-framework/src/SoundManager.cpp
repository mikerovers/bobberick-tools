#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
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
		const auto pChunk = Mix_LoadWAV("assets/music/effects/arrow-swoosh-2.ogg");
		
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

void SoundManager::playSound(const std::string& id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
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

