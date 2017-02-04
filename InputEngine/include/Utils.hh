#pragma once

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif

BOOL CALLBACK	CreateDeviceCallback(LPCDIDEVICEINSTANCE instance, LPVOID reference);
BOOL CALLBACK	enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* GamePad);