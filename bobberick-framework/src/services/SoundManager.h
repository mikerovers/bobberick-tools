#ifndef BOBBERICK_TOOLS_SOUNDMANAGER_H
#define BOBBERICK_TOOLS_SOUNDMANAGER_H

#include <SDL.h>
#include <string>
#include <map>
#include <SDL_mixer.h>
#include "Service.h"

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager : public Service
{
public:
	void init() override;

	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return  s_pInstance;
		}
		return  s_pInstance;
	}

	bool load(const std::string& file_name, const std::string& id, const sound_type type);

	void playSound(int const channel, std::string id, int loop);
	void playMusic(const std::string& id, int loop);

	void stopMusic();
	
	void pauseMusic();
	void resumeMusic();

	void stopAllSounds();
	void stopSound(int const channel);

	void pauseSound(int const channel);
	void resumeSound(int const channel);

	void pauseAllChannels();
	void resumeAllChannels();

	bool isSoundPlaying(int const channel) const;

	void clean() override;

	SoundManager();
	~SoundManager();

private:
	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
	int channelCount;

	void fadeOut();

	SoundManager(const SoundManager&);
	SoundManager &operator=(const SoundManager&);
};

typedef SoundManager TheSoundManager;

#endif //BOBBERICK_TOOLS_SOUNDMANAGER_H
