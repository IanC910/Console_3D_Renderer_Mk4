#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <ctime>

#include "VectorMath.h" // includes <math.h>

const double PI = 2 * acos(0);

class Debug
{
public:
	static void logInfo(std::string, std::string);
	static void logError(std::string, std::string);

private:
	static std::ofstream* logFile;

	Debug();
};


#endif
