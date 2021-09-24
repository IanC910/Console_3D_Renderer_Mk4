#include "Screen.hpp"
#include "Vector2D.hpp"
#include <Windows.h>
#include <math.h>
#include <string>

const double pi = 2 * acos(0);

Screen::Screen()
{
	width = 120;
	height = 35;

	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screen = new wchar_t[width * height];
	dwBytesWritten = 0;
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

Screen::Screen(int w, int h)
{
	width = w;
	height = h;

	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screen = new wchar_t[width * height];
	dwBytesWritten = 0;
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

void Screen::startScreen()
{
	SetConsoleActiveScreenBuffer(hConsole);
}

void Screen::update()
{	
	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screen[width * height - 1] = '\0';
	WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0,0 }, &dwBytesWritten);
}

void Screen::write(int x, int y, wchar_t c)
{
	screen[width * (height - y - 1) + x] = c;
}

void Screen::write(Vector2D POS, wchar_t c)
{
	screen[width * (height - static_cast<int>(POS.y) - 1) + static_cast<int>(POS.x)] = c;
}

void Screen::writeString(Vector2D POS, std::string s)
{
	for (int n = 0; n < s.size(); n++)
	{
		screen[width * (height - static_cast<int>(POS.y) - 1) + static_cast<int>(POS.x + n)] = s[n];
	}
}

void Screen::setBlank()
{
	for (int i = 0; i < width * height; i++)
	{
		screen[i] = ' ';
	}
}

bool Screen::isValid(Vector2D P)
{
	return ((P.y < height) && (P.y > 0) && (P.x < width) && (P.x > 0));
}

Screen::~Screen()
{
	delete[] screen;
}