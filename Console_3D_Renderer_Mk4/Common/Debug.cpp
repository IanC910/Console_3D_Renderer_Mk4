
#include "Debug.h"

std::ofstream* Debug::logFile = nullptr;

void Debug::logInfo(std::string tag, std::string message)
{
	if (logFile == nullptr)
	{
		logFile = new std::ofstream();
		logFile->open("../renderer_log.txt");
		logFile->clear();
	}

	*logFile << "INFO: [" << tag << "] " << message << "\n";
	std::cout << "INFO: [" << tag << "] " << message << "\n";
}

void Debug::logError(std::string tag, std::string message)
{
	if (logFile == nullptr)
	{
		logFile = new std::ofstream();
		logFile->open("../renderer_log.txt");
		logFile->clear();
	}

	*logFile << "\nERROR: [" << tag << "] " << message << "\n\n";
	std::cout << "\nERROR: [" << tag << "] " << message << "\n\n";
}