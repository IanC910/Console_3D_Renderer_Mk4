#ifndef SCREEN_H
#define SCREEN_H

#include "Vector2D.hpp"
#include <Windows.h>
#include <string>

class Screen
{
public:

	// Screen Dimensions
	int width;
	int height;

	Screen();
	// Default Constructor initializes all variables

	Screen(int w, int h);
	// Constructor takes in dimensions for the screen

	void startScreen();
	// Starts the screen buffer
	// Before calling this, the console will behave normally

	void update();
	// Updates terminal by printing the screen array

	void write(int x, int y, wchar_t c);
	// Writes charcater c to the screen array at (x , y)

	void write(Vector2D POS, wchar_t c);
	// Overloaded version that takes in Vector2D POS rather than two individual coordinate components

	void writeString(Vector2D POS, std::string s);
	// Writes a string to the screen, starting at position POS

	void setBlank();

	bool isValid(Vector2D P);
	// Checks if the coordinate is inside screen boundaries

	~Screen();

private:
	// Things from the youtube video: https://www.youtube.com/watch?v=xW8skO7MFYw
	wchar_t* screen;
	DWORD dwBytesWritten;
	HANDLE hConsole;
};

#endif

