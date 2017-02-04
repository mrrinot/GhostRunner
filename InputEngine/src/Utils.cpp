#include "Utils.hh"
#include "InputEngine.hh"

#include <iostream>

BOOL CALLBACK	CreateDeviceCallback(LPCDIDEVICEINSTANCE instance, LPVOID reference)
{
	//std::cout << "Kikoo !" << std::endl;
	HRESULT					result;
	LPDIRECTINPUTDEVICE8	GamePad;

	// Création du périphérique
	result = ((LPDIRECTINPUT8) reference)->CreateDevice(instance->guidInstance, &GamePad, NULL);

	// Gestion des erreurs
	if (!FAILED(result))
		InputEngine::getInstance().AddGamePad(GamePad);

	return DIENUM_CONTINUE;
}

BOOL CALLBACK	enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* GamePad)
{
	DIPROPRANGE propRange;
	propRange.diph.dwSize = sizeof(DIPROPRANGE);
	propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	propRange.diph.dwHow = DIPH_BYID;
	propRange.diph.dwObj = instance->dwType;
	propRange.lMin = -1000;
	propRange.lMax = +1000;

	// Set the range for the axis
	if (FAILED(((LPDIRECTINPUTDEVICE8) GamePad)->SetProperty(DIPROP_RANGE, &propRange.diph))) {
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}