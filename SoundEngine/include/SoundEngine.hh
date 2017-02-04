#pragma once

#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking
#include <iostream>
#include <string>
#include <map>

class SoundEngine
{
private:
	FMOD::System								*_sys;
	std::map<std::string, FMOD::Sound *>		_lib;
	std::map<std::string, FMOD::Channel *>		_chan;
	std::map<std::string, FMOD::ChannelGroup *>	_chanGrp;

	static SoundEngine							_classInstance;

public:
	static SoundEngine	&getInstace();

	SoundEngine(int chanNb = 32);
	~SoundEngine();

	bool				isSetSound(const std::string &name);
	bool				isExistSound(const std::string &name);
	bool				isSetChannel(const std::string &name);
	bool				isExistChannel(const std::string &name);
	bool				isSetChannelGroup(const std::string &name);
	bool				isExistChannelGroup(const std::string &name);


	void				PauseAllChannel();
	void				StopAllChannel();
	void				ReleaseAllSound();

	bool				LoadSound(const std::string &name, const std::string &path);
	bool				PlaySoundOnChannel(const std::string &chan, const std::string &sound, const std::string &group = "Master",
										   bool loop = false, bool overide = false, bool paused = false);
	bool				ReleaseSound(const std::string &name);

	bool				AddChannel(const std::string &chan);
	bool				StopChannel(const std::string &chan);
	bool				PlayChannel(const std::string &chan);
	bool				PauseChannel(const std::string &chan);
	bool				RemoveChannel(const std::string &chan);

	bool				AddChannelGroup(const std::string &group);
	bool				SetVolumeChannelGroup(const std::string &group, float vol);
	bool				SetMuteChannelGroup(const std::string &group, bool muted);
	bool				RemoveChannelGroup(const std::string &group);
	bool				ParentingChannelGroup(const std::string &sonGroup, const std::string &dadGroup);
	bool				AddChannelToChannelGroup(const std::string &chan, const std::string &group);
	
	float				GetVolumeChannelGroup(const std::string &group);

	bool				IsChanPlaying(const std::string &chan);
	bool				Update();
	
};

// {Add/Rm/Pause/play} chan / release song / ChanGroupe ? / SoundGroupe ?	