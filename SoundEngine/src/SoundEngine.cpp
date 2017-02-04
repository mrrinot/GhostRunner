#include "SoundEngine.hh"
#include "AudioExeption.hh"
#include "NotFoundExeption.hh"
#include "IdAlreadyTakeExeption.hh"

SoundEngine	SoundEngine::_classInstance = SoundEngine();

SoundEngine	&SoundEngine::getInstace()
{
	return _classInstance;
}

SoundEngine::SoundEngine(int chanNb)
{
	int				driverCount = 0;
	unsigned int	version = 0;


	if (FMOD::System_Create(&_sys) != FMOD_OK)
		throw AudioExeption("Can't create FMOD systeme");
	if (_sys->getNumDrivers(&driverCount) != FMOD_OK || _sys->getVersion(&version) != FMOD_OK)
		throw AudioExeption("Error");
	if (version < FMOD_VERSION)
	{
		//"FMOD lib version " << version << " doesn't match header version " << FMOD_VERSION
		throw AudioExeption("Bad version of FMOD");
	}
	if (driverCount == 0)
		throw AudioExeption("Driver not found");

	_sys->init(chanNb, FMOD_INIT_NORMAL, NULL);

	_chanGrp["Master"] = NULL;
	_sys->getMasterChannelGroup(&_chanGrp["Master"]);
}

SoundEngine::~SoundEngine()
{
	StopAllChannel();
	ReleaseAllSound();
	_sys->close();
	_sys->release();
}



// ----------------------------------------------------------------- //
// --     ALL FUNCTIONS                                           -- //
// ----------------------------------------------------------------- //

void			SoundEngine::StopAllChannel()
{
	for (std::map<std::string, FMOD::Channel *>::iterator it = _chan.begin(); it != _chan.end(); ++it)
		it->second->stop();
}

void			SoundEngine::PauseAllChannel()
{
	for (std::map<std::string, FMOD::Channel *>::iterator it = _chan.begin(); it != _chan.end(); ++it)
		it->second->setPaused(true);
}

void			SoundEngine::ReleaseAllSound()
{
	for (std::map<std::string, FMOD::Sound *>::iterator it = _lib.begin(); it != _lib.end(); ++it)
		it->second->release();
	_lib.erase(_lib.begin(), _lib.end());
}



// ----------------------------------------------------------------- //
// --     TOOLS                                                   -- //
// ----------------------------------------------------------------- //

bool				SoundEngine::isExistChannelGroup(const std::string &name)
{
	return (_chanGrp.count(name) != 0);
}

bool				SoundEngine::isSetChannelGroup(const std::string &name)
{
	return (isExistChannelGroup(name) && _chanGrp[name] != NULL);
}

bool				SoundEngine::isExistChannel(const std::string &name)
{
	return (_chan.count(name) != 0);
}

bool				SoundEngine::isSetChannel(const std::string &name)
{
	return (isExistChannel(name) && _chan[name] != NULL);
}

bool				SoundEngine::isExistSound(const std::string &name)
{
	return (_lib.count(name) != 0);
}

bool				SoundEngine::isSetSound(const std::string &name)
{
	return (isExistSound(name) && _lib[name] != NULL);
}

bool				SoundEngine::Update()
{
	if (_sys->update() != FMOD_OK)
		return false;
	return true;
}



// ----------------------------------------------------------------- //
// --     SOUND MANAGEMENT                                        -- //
// ----------------------------------------------------------------- //

bool			SoundEngine::LoadSound(const std::string &name, const std::string &path)
{
	if (isExistSound(name))
		throw IdAlreadyTakeExeption("Sound already exist");

	_lib[name] = NULL;
	FMOD_RESULT res;

	if ((res = _sys->createSound(path.c_str(), FMOD_DEFAULT, 0, &_lib[name])) != FMOD_OK) // FMOD_DEFAULT // _lib[name]->setMode(FMOD_LOOP_OFF);
	{
		_lib.erase(name);
		// std::cout << res << " : " << path.c_str() << std::endl;
		return false;
	}

	return true;
}

bool				SoundEngine::ReleaseSound(const std::string &sound)
{
	if (isExistSound(sound))
		return true;
	if (isSetSound(sound) && _lib[sound]->release() != FMOD_OK)
		return false;
	_lib.erase(sound);
	return true;
}

bool				SoundEngine::PlaySoundOnChannel(const std::string &chan, const std::string &sound, const std::string &group,  bool loop, bool overide, bool paused)
{
	bool			result;

	if (!isSetSound(sound))
		throw NotFoundExeption("Sound not found");
	if (!isExistChannel(chan))
		throw NotFoundExeption("Channel not found");

	if (loop)
		_lib[sound]->setMode(FMOD_LOOP_NORMAL);
	else
		_lib[sound]->setMode(FMOD_LOOP_OFF);

	if (!overide && IsChanPlaying(chan))
		throw IdAlreadyTakeExeption("Channel already exist");


	if (_sys->playSound(_lib[sound], 0, paused, &_chan[chan]) != FMOD_OK)
		return false;
	if ((result = AddChannelToChannelGroup(chan, group)) != true)
	{
		_chan[chan]->stop();
		return result;
	}

	return true;
}



// ----------------------------------------------------------------- //
// --     CHANNEL MANAGEMENT                                      -- //
// ----------------------------------------------------------------- //

bool				SoundEngine::AddChannel(const std::string &chan)
{
	if (isExistChannel(chan))
		throw IdAlreadyTakeExeption("Channel already exist");
	_chan[chan] = NULL;
	return true;
}

bool				SoundEngine::StopChannel(const std::string &chan)
{
	if (!isSetChannel(chan))
		throw NotFoundExeption("Channel not found");
	if (_chan[chan]->stop() != FMOD_OK)
		return false;
	return true;
}

bool				SoundEngine::PlayChannel(const std::string &chan)
{
	if (!isSetChannel(chan))
		throw NotFoundExeption("Channel not found");
	if (_chan[chan]->setPaused(false) != FMOD_OK)
		return false;
	return true;
}

bool				SoundEngine::PauseChannel(const std::string &chan)
{
	if (!isSetChannel(chan))
		throw NotFoundExeption("Channel not found");
	if (_chan[chan]->setPaused(true) != FMOD_OK)
		return false;
	return true;
}

bool				SoundEngine::RemoveChannel(const std::string &chan)
{
	bool			result;

	if ((result = StopChannel(chan)) == true)
		_chan.erase(chan);
	return result;
}


bool				SoundEngine::IsChanPlaying(const std::string &chan)
{
	bool			isPlaying;

	if (!isSetChannel(chan) || _chan[chan]->isPlaying(&isPlaying) != FMOD_OK)
		return false;
	return isPlaying;
}



// ----------------------------------------------------------------- //
// --     ChannelGroup Management                                 -- //
// ----------------------------------------------------------------- //

bool				SoundEngine::AddChannelGroup(const std::string &group)
{
	if (isExistChannelGroup(group))
		throw IdAlreadyTakeExeption("ChannelGroup already exist");
	_chanGrp[group] = NULL;
	if (_sys->createChannelGroup(group.c_str(), &_chanGrp[group]) == FMOD_OK && ParentingChannelGroup(group, "Master") == true)
		return true;
	return false;
}

bool				SoundEngine::SetVolumeChannelGroup(const std::string &group, float vol)
{
	if (!isSetChannelGroup(group))
		throw NotFoundExeption("ChannelGroup not found");
	if (_chanGrp[group]->setVolume(vol) == FMOD_OK)
		return true;
	return false;
}

bool				SoundEngine::SetMuteChannelGroup(const std::string &group, bool muted)
{
	if (!isSetChannelGroup(group))
		throw NotFoundExeption("ChannelGroup not found");
	if (_chanGrp[group]->setMute(muted) == FMOD_OK)
		return true;
	return false;
}

bool				SoundEngine::RemoveChannelGroup(const std::string &group)
{
	if (!isSetChannelGroup(group))
		throw NotFoundExeption("ChannelGroup not found");
	if (_chanGrp[group]->release() == FMOD_OK)
	{
		_chanGrp.erase(group);
		return true;
	}
	return false;
}

bool				SoundEngine::ParentingChannelGroup(const std::string &sonGroup, const std::string &dadGroup)
{
	if (!isSetChannelGroup(sonGroup) || !isSetChannelGroup(dadGroup))
		throw NotFoundExeption("ChannelGroup not found");
	if (_chanGrp[dadGroup]->addGroup(_chanGrp[sonGroup]) == FMOD_OK)
		return true;
	return false;
}

bool			SoundEngine::AddChannelToChannelGroup(const std::string &chan, const std::string &group)
{
	if (!isSetChannelGroup(group))
		throw NotFoundExeption("ChannelGroup not found");
	if (!isSetChannel(chan))
		throw NotFoundExeption("Channel not found");
	if (_chan[chan]->setChannelGroup(_chanGrp[group]) == FMOD_OK)
		return true;
	return false;
}


float				SoundEngine::GetVolumeChannelGroup(const std::string &group)
{
	float			vol = -1.0f;

	if (isSetChannelGroup(group))
		//	return SoundEngineResult::CHANNELGROUP_NOT_FOUND;
		if (_chanGrp[group]->getVolume(&vol) == FMOD_OK)
			return vol;
	return -1.0f;
}