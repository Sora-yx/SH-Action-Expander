#include "pch.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include "anims.h"

extern "C"
{
	__declspec(dllexport) void PrintMessage(const char* message)
	{
		std::cout << message << "\n" << std::endl;
	}


	__declspec(dllexport) void Init()
	{
		PrintMessage("Action Expander says Hello from C++\n");
		InitNewAnims();
	}

}