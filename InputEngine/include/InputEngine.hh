#pragma once

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif
#include "InputDevice.hh"
#include <vector>

class InputEngine
{
private:
  static InputEngine			_ClassInstance;

  LPDIRECTINPUT8				_directInput;
  std::vector<InputDevice *>	_devices;

public:
  InputEngine();
  ~InputEngine();
  static InputEngine			&getInstance();

  void						AddGamePad(const LPDIRECTINPUTDEVICE8 &);
  std::vector<Inputs>			GetInput() const;
  Inputs						GetInput(int) const;

  std::size_t					countDevice() const;
};

