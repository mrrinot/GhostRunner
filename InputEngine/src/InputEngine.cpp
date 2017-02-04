#include "InputEngine.hh"
#include "Gamepad.hh"
#include "KeyBoard.hh"
#include "Utils.hh"

#include <iostream>


InputEngine InputEngine::_ClassInstance = InputEngine();


InputEngine					&InputEngine::getInstance()
{
  return _ClassInstance;
}

InputEngine::InputEngine()
{
  HRESULT		result = 0;
  HINSTANCE	instance;

  instance = GetModuleHandle(NULL);

  // Création de l'objet DirectInput
  result = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL);

  // Gestion des erreurs
  if (FAILED(result))
  {
    //std::cout << "C'etait donc toi depuis le debut !" << std::endl;
    throw std::exception(); // TODO : Custom 
    return;
  }

  // Get KeyBoard
  LPDIRECTINPUTDEVICE8	keyboard;

  if (FAILED(_directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL)))
  {
    std::cout << "Getting KeyBoard : Fail !" << std::endl;
    throw std::exception(); // TODO : Custom 
  }
  else
    _devices.push_back(new KeyBoard(keyboard));


  // Get All GamePad
  result = _directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, &CreateDeviceCallback, (void *)_directInput, DIEDFL_ATTACHEDONLY);

  // Gestion des erreurs
  if (FAILED(result))
  {
    //std::cout << "C'etait donc toi depuis le debut ! SALOW !" << std::endl;
    throw std::exception(); // TODO : Custom 
    return;
  }
}


InputEngine::~InputEngine()
{
  for (auto device : _devices)
    delete device;
  _directInput->Release();
}

void						InputEngine::AddGamePad(const LPDIRECTINPUTDEVICE8 &device)
{
  _devices.push_back(new Gamepad(device));
}

std::size_t					InputEngine::countDevice() const
{
  return _devices.size();
}

std::vector<Inputs>				InputEngine::GetInput() const
{
  std::vector<Inputs>			ret;

  for (InputDevice *device : _devices)
    ret.push_back(device->GetInput());
  //ret.unique();

  return ret;
}

Inputs							InputEngine::GetInput(int i) const
{
  try {
    return _devices.at(i)->GetInput();
  }
  catch (const std::out_of_range&) {
    return NoInput;
  }
}