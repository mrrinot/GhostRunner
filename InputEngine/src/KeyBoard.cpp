#include "KeyBoard.hh"
#include <iostream>


KeyBoard::KeyBoard(LPDIRECTINPUTDEVICE8 device)
{
	if (FAILED(device->SetCooperativeLevel(NULL, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		//std::cout << "First" << std::endl;
		throw std::exception();
	}

	if (FAILED(device->SetDataFormat(&c_dfDIKeyboard)))
	{
		//std::cout << "Second" << std::endl;
		throw std::exception();
	}

	_device = device;

	setDefaultButtons();
}


KeyBoard::~KeyBoard()
{
}


Inputs					KeyBoard::GetInput() const
{
	Inputs					ret;
	HRESULT					result;


	ret.X_Axis = 0;
	ret.Y_Axis = 0;
	ret.Z_Axis = 0;
	ret.RZ_Axis = 0;

	ret.POV = -1;

	result = _device->Acquire();
	while (result == DIERR_INPUTLOST) {
		result = _device->Acquire();
	}

	// Fatal Error
	if ((result == DIERR_INVALIDPARAM) || (result == DIERR_NOTINITIALIZED)) {
		std::cout << "Keyboard: Fatal Error" << std::endl;
		return ret;
	}

	char state[256];

	if (_device->GetDeviceState(((sizeof(unsigned char)) << 8), (void*)state) == DI_OK) {
		for (int i = 0; i < 256; i++)
			if (state[i]) {
				if (_keyMap.find(i) != _keyMap.end())
					ret.Buttons.push_back(_keyMap.at(i));
				else
					ret.UnisignedButtons.push_back(i);
			}
	}
	else
		return ret;
	return ret;
}

bool					KeyBoard::IsGamepad() const
{
	return false;
}

bool					KeyBoard::Connected() const
{
	return true;
}

void					KeyBoard::setDefaultButtons()
{
	AddKeyMapping(DIK_UP, "Up");
	AddKeyMapping(DIK_DOWN, "Down");
	AddKeyMapping(DIK_LEFT, "Left");
	AddKeyMapping(DIK_RIGHT, "Right");
	AddKeyMapping(DIK_RETURN, "Enter");
	AddKeyMapping(DIK_Q, "A");
	AddKeyMapping(DIK_W, "B");
	AddKeyMapping(DIK_E, "X");
	AddKeyMapping(DIK_R, "Y");
	AddKeyMapping(DIK_ESCAPE, "Start");
}