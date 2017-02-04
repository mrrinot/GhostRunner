#pragma once

#include <string>
#include <list>
#include <map>

typedef struct s_Inputs
{
	std::list<std::string>		Buttons;
	std::list<int>				UnisignedButtons;

	int							X_Axis;
	int							Y_Axis;
	int							Z_Axis;
	int							RZ_Axis;

	int							POV;

}				Inputs;

const Inputs NoInput = { std::list<std::string>(), std::list<int>(), 0, 0, 0, 0, -1 };

class InputDevice
{
protected:
	std::map<int, std::string>	_keyMap;

public:
	~InputDevice() {}

	virtual Inputs					GetInput() const = 0;
	virtual bool					IsGamepad() const = 0;
	virtual bool					Connected() const = 0;

	virtual void					setDefaultButtons() = 0;


	void							AddKeyMapping(int button, std::string key)
	{
		_keyMap.erase(button);
		_keyMap.insert(std::map<int, std::string>::value_type(button, key));
	}

	void							RemoveKeyMappingByButton(int button)
	{
		_keyMap.erase(button);
	}

	void							RemoveKeyMapping(std::string key)
	{
		for (auto it = _keyMap.begin(); it != _keyMap.end(); ++it)
			if (it->second == key)
			{
				_keyMap.erase(it);
				return;
			}
	}

	void							ClearMappings()
	{
		_keyMap.clear();
	}
};