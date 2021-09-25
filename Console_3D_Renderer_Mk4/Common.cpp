#include "Common.h"

std::ofstream* Debug::logFile = nullptr;

void Debug::log(std::string message)
{
	if (logFile == nullptr)
	{
		logFile = new std::ofstream();
		logFile->open("../renderer_log.txt");
		logFile->clear();
	}

	*logFile << message << "\n";
	std::cout << message << "\n";
}