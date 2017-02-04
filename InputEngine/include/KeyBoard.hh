#pragma once
#include "InputDevice.hh"
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif

class KeyBoard : public InputDevice
{
private:
	LPDIRECTINPUTDEVICE8	_device;


public:
	KeyBoard(LPDIRECTINPUTDEVICE8);
	~KeyBoard();

	// InputDevice Virtual
	virtual Inputs					GetInput() const;
	virtual bool					IsGamepad() const;
	virtual bool					Connected() const;

	virtual void					setDefaultButtons();
};

