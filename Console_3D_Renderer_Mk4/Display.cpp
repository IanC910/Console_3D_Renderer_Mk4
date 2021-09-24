
#include "Display.h"

int Display::width = 120;
int Display::height = 35;

wchar_t* Display::screenArray = nullptr;
DWORD Display::dwBytesWritten;
HANDLE Display::consoleHandle;

void Display::initDisplay(int initWidth, int initHeight)
{
	width = initWidth;
	height = initHeight;

	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screenArray = new wchar_t[width * height];
	dwBytesWritten = 0;
	consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleHandle);

	setBlank();
}

void Display::update()
{	
	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screenArray[width * height - 1] = '\0';
	WriteConsoleOutputCharacter(consoleHandle, screenArray, width * height, {0, 0}, &dwBytesWritten);
}

void Display::write(int x, int y, wchar_t c)
{
	screenArray[width * (height - y - 1) + x] = c;
}

void Display::write(Vector2 pos, wchar_t c)
{
	screenArray[width * (height - static_cast<int>(pos.y) - 1) + static_cast<int>(pos.x)] = c;
}

void Display::write(Vector2 pos, std::string s)
{
	for (int n = 0; n < s.size(); n++)
	{
		screenArray[width * (height - static_cast<int>(pos.y) - 1) + static_cast<int>(pos.x + n)] = s[n];
	}
}

void Display::setBlank()
{
	for (int i = 0; i < width * height; i++)
	{
		screenArray[i] = ' ';
	}
}

bool Display::isValid(Vector2 P)
{
	return ((P.y < height) && (P.y > 0) && (P.x < width) && (P.x > 0));
}