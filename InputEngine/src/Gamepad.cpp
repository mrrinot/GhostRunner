#include "Gamepad.hh"
#include "Utils.hh"

#include <iostream>

Gamepad::Gamepad(const LPDIRECTINPUTDEVICE8 &device)
{
  _device = device;
  std::cout << "Hi, I'm the gamepad !" << std::endl;

  HRESULT					result;

  result = _device->SetDataFormat(&c_dfDIJoystick2);
  if (FAILED(result))
  {
    std::cout << "GamePad: Cannot set Data Format" << std::endl;
    // TODO throw
  }

  result = _device->EnumObjects(&enumAxesCallback, _device, DIDFT_AXIS);
  if (FAILED(result)) {
    std::cout << "GamePad: Cannot Get Capabilities" << std::endl;
    // TODO throw
  }

  DIDEVCAPS capabilities;

  capabilities.dwSize = sizeof(DIDEVCAPS);
  result = _device->GetCapabilities(&capabilities);
  if (FAILED(result)) {
    std::cout << "GamePad: Cannot Get Capabilities" << std::endl;
    // TODO throw
  }
  else
  {
    _nbBtn = capabilities.dwButtons;
    _nbAxis = capabilities.dwAxes;
    _nbPov = capabilities.dwPOVs;
    std::cout << "GamePad: Has " << _nbBtn << " Buttons, " << _nbAxis << " Axis, and " << _nbPov << " POV." << std::endl;
  }

  setDefaultButtons();
}


Gamepad::~Gamepad()
{
  _device->Unacquire();
  _device->Release();
  _device = NULL;
}

Inputs						Gamepad::GetInput() const
{
  DIJOYSTATE2				state;
  Inputs					ret;
  HRESULT					result;

  //std::cout << "GamePad: Test" << std::endl;
  ret.X_Axis = 0;
  ret.Y_Axis = 0;
  ret.Z_Axis = 0;
  ret.RZ_Axis = 0;

  ret.POV = -1;

  result = _device->Poll();
  if (FAILED(result)) {
    result = _device->Acquire();
    while (result == DIERR_INPUTLOST) {
      result = _device->Acquire();
    }

    // Fatal Error
    if ((result == DIERR_INVALIDPARAM) || (result == DIERR_NOTINITIALIZED)) {
      std::cout << "GamePad: Fatal Error" << std::endl;
      return ret;
    }

    // another app has controle of the device
    if (result == DIERR_OTHERAPPHASPRIO) {
      std::cout << "GamePad: Other proprio" << std::endl;
      return ret;
    }
  }
  result = _device->GetDeviceState(sizeof(state), (LPVOID)&state);

  if (FAILED(result))
    return ret;

  ret.X_Axis = state.lX;
  ret.Y_Axis = state.lY;
  ret.Z_Axis = state.lZ;
  ret.RZ_Axis = state.lRz;

  ret.POV = state.rgdwPOV[0];

  if (ret.POV != -1)
    ret.POV /= 4500;

  for (auto i = 0u; i < _nbBtn; i++)
    if (state.rgbButtons[i] & 0x80)
    {
      if (_keyMap.find(i) != _keyMap.end())
        ret.Buttons.push_back(_keyMap.at(i));
      else
        ret.UnisignedButtons.push_back(i);
    }

  return ret;
}

bool					Gamepad::IsGamepad() const
{
  return true;
}

bool					Gamepad::Connected() const
{
  HRESULT				result = _device->Poll();
  int					cnt = 0;

  if (FAILED(result)) {
    result = _device->Acquire();
    while (result == DIERR_INPUTLOST && ++cnt < 15) {
      result = _device->Acquire();
    }

    // Fatal Error
    if ((result == DIERR_INVALIDPARAM) || (result == DIERR_NOTINITIALIZED)) {
      return false;
    }
  }
  return true;
}

void							Gamepad::setDefaultButtons()
{
  AddKeyMapping(0, "A");
  AddKeyMapping(1, "B");
  AddKeyMapping(2, "X");
  AddKeyMapping(3, "Y");
  AddKeyMapping(4, "LB");
  AddKeyMapping(5, "RB");
  AddKeyMapping(6, "Select");
  AddKeyMapping(7, "Start");
  AddKeyMapping(9, "LT");
  AddKeyMapping(8, "RT");
  AddKeyMapping(10, "LStick");
  AddKeyMapping(11, "RStick");
}