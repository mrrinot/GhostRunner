#include "SoundEngine.hh"
#include "AudioExeption.hh"
#include <string>
#include <iostream>
#include <sstream>

void		display_error(bool result)
{
	if (result)
		std::cout << "Ok" << std::endl;
	else
		std::cout << "PAS OK" << std::endl;
}

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>


int	main() {
	char* buffer;

	// Get the current working directory: 
	if ((buffer = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");
	else
	{
		printf("'%s' \n", buffer);
		free(buffer);
	}

	try {
		std::string			input;
		SoundEngine			DJ = SoundEngine();
		std::stringstream	ss;
		float				vol;

		char			*pewchan[] = { "Pew1", "Pew2", "Pew3" };
		unsigned int	cursor = 0;



		std::cout << "Init Sound" << std::endl;
		display_error(DJ.LoadSound("Test", "Debug\\Resources\\Music\\23 becassine is my cousine.mp3"));
		display_error(DJ.LoadSound("Arg", "Debug\\Resources\\Music\\WilhelmScream.wav"));

		std::cout << "Init ChannelGroup" << std::endl;
		display_error(DJ.AddChannelGroup("Music"));
		display_error(DJ.AddChannelGroup("FX"));
		
		std::cout << "Init Channel" << std::endl;
		display_error(DJ.AddChannel("Kikoo"));
		display_error(DJ.AddChannel("Pew1"));
		display_error(DJ.AddChannel("Pew2"));
		display_error(DJ.AddChannel("Pew3"));

		std::cout << "Set sound" << std::endl;
		display_error(DJ.PlaySoundOnChannel("Kikoo", "Test", "Music", true));

		while (true) {
			input.empty();
			std::getline(std::cin, input);

			if (input == "q")
				break;
			else if (input == "p")
			{
				display_error(DJ.PauseChannel("Kikoo"));
				std::cout << "Pause" << std::endl;
			}
			else if (input == "pp")
			{
				display_error(DJ.PlayChannel("Kikoo"));
				std::cout << "Pause" << std::endl;
			}
			else if (input == "o")
			{
				display_error(DJ.PlaySoundOnChannel(pewchan[cursor++ % 3], "Arg", "FX", false, true));
				std::cout << "Pew" << std::endl;
			}
			else if (input == "mm")
			{
				display_error(DJ.SetMuteChannelGroup("Master", true));
				std::cout << "Mute Master" << std::endl;
			}
			else if (input == "um")
			{
				display_error(DJ.SetMuteChannelGroup("Master", false));
				std::cout << "Unmute Master" << std::endl;
			}
			else
			{
				ss.clear();
				ss << input;

				input = "";
				ss >> input;
				ss >> vol;


				display_error(DJ.SetVolumeChannelGroup(input, vol));
				std::cout << "Set " << input << " to " << vol << std::endl;
			}
			//DJ.Update();
		}
	}
	catch (const AudioExeption &e) {
		std::cout << "AudioExeption : " << e.what() << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "std::exception : " << e.what() << std::endl;
	}

	return 0;
}
