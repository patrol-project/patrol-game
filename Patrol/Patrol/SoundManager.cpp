#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance;

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

void SoundManager::playMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::clearSoundMap() {
	for (auto i = m_music.begin(); i != m_music.end(); i++) {
		if (i->second != nullptr) {
			Mix_FreeMusic(i->second);
			i->second = nullptr;
		}
	}
	m_music.clear();

	for (auto j = m_sfxs.begin(); j != m_sfxs.end(); j++) {
		if (j->second != nullptr) {
			Mix_FreeChunk(j->second);
			j->second = nullptr;
		}
	}
	m_sfxs.clear();
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if (pMusic == 0)
		{
			//std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		// set the volume for the sound effect
		Mix_VolumeChunk(pChunk, 10);
		if (pChunk == 0)
		{
			// std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	// set the volume for the theme music
	Mix_VolumeMusic(10);
}
