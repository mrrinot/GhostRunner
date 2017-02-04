#pragma once

#include "InputDevice.hh"
#include <map>
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif


class Gamepad : public InputDevice
{
private:
	LPDIRECTINPUTDEVICE8		_device;
	GUID						_InstanceID;
	//std::list<std::string>		_targets;
	//std::map<int, std::string>	_actions;

	DWORD						_nbBtn;
	DWORD						_nbAxis;
	DWORD						_nbPov;

public:
	Gamepad(const LPDIRECTINPUTDEVICE8 &);
	~Gamepad();

	// InputDevice Virtual
	virtual Inputs					GetInput() const;
	virtual bool					IsGamepad() const;
	virtual bool					Connected() const;

	virtual void					setDefaultButtons();

};

