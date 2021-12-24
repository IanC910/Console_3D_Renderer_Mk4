#ifndef Display_H
#define Display_H

#include "Common/Common.h"

class Display
{
public:

	// Display Dimensions
	static int width;
	static int height;

	static void initDisplay(int, int);
	// Starts the Screen buffer with size width by height
	// Before calling this, the console will behave normally

	static void update();
	// Updates terminal by printing the Display array

	static void write(int, int, wchar_t);
	// Writes a wide charcater to the Display array at the position specificed by two integer coordinates

	static void write(Vec2, wchar_t);
	// Writes a wide character to the Display array at the position specified by the vector

	static void write(Vec2, std::string);
	// Writes a string left to right to the Display array, starting at the position specified by the vector

	static void drawTriangle(Vec2, Vec2, Vec2, wchar_t);
	// draws triangle at 3 points with a given brightness from 0 to 1

	static void setBlank();

	static bool isValid(Vec2);
	// Checks if the coordinate is inside Display boundaries

private:
	// Things from the youtube video: https://www.youtube.com/watch?v=xW8skO7MFYw
	static wchar_t* screenArray;
	static DWORD bytesWritten;
	static HANDLE consoleHandle;

	Display();
};

#endif

