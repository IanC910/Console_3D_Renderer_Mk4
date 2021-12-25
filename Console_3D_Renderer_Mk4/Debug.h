#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>

class Debug
{
public:
	static void info(std::string, std::string);
	static void error(std::string, std::string);

private:
	static std::ofstream* logFile;

	Debug();
};

#endif