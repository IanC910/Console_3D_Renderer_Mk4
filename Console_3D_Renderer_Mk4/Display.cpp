
#include "Display.h"

int Display::width = 120;
int Display::height = 35;

wchar_t* Display::screenArray = nullptr;
DWORD Display::dwBytesWritten;
HANDLE Display::consoleHandle;

void Display::initDisplay(int initWidth, int initHeight)
{
	Debug::log("Initializing Display...");

	width = initWidth;
	height = initHeight;

	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screenArray = new wchar_t[width * height];
	dwBytesWritten = 0;
	consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleHandle);

	setBlank();

	Debug::log("Display Initialized");
}

void Display::update()
{	
	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screenArray[width * height - 1] = '\0';
	WriteConsoleOutputCharacter(consoleHandle, screenArray, width * height, {0, 0}, &dwBytesWritten);
}

void Display::write(int x, int y, wchar_t c)
{
	if(isValid(Vector2(x, y)))
		screenArray[width * (height - y - 1) + x] = c;
}

void Display::write(Vector2 pos, wchar_t c)
{
	if(isValid(pos))
		screenArray[width * (height - static_cast<int>(pos.y) - 1) + static_cast<int>(pos.x)] = c;
}

void Display::write(Vector2 pos, std::string s)
{
	for (int n = 0; n < s.size(); n++)
	{
		if(isValid(Vector2(pos)))
			screenArray[width * (height - static_cast<int>(pos.y) - 1) + static_cast<int>(pos.x + n)] = s[n];
	}
}

void Display::drawTriangle(Vector2 vertex0, Vector2 vertex1, Vector2 vertex2, wchar_t c)
{
	/*// Draw only Vertices
	write(vertex0, '0');
	write(vertex1, '1');
	write(vertex2, '2');
	return;*/


	Vector2* lowHorizV = &vertex0;
	Vector2* midHorizV = &vertex1;
	Vector2* highHorizV = &vertex2;
	
	Vector2* lowVertV = &vertex0;
	Vector2* midVertV = &vertex1;
	Vector2* highVertV = &vertex2;

	wchar_t charToDraw;

	// Sort vertices of triangle by position in the 2D screen plane
	Vector2* tempV; // for swapping purposes

	// Sort by horizontal position
	if(midHorizV->x < lowHorizV->x)
	{
		tempV = midHorizV;
		midHorizV = lowHorizV;
		lowHorizV = tempV;
	}

	if (highHorizV->x < lowHorizV->x)
	{
		tempV = highHorizV;
		highHorizV = lowHorizV;
		lowHorizV = tempV;
	}

	if (highHorizV->x < midHorizV->x)
	{
		tempV = highHorizV;
		highHorizV = midHorizV;
		midHorizV = tempV;
	}

	// Sort by vertical position
	if (midVertV->y < lowVertV->y)
	{
		tempV = midVertV;
		midVertV = lowVertV;
		lowVertV = tempV;
	}

	if (highVertV->y < lowVertV->y)
	{
		tempV = highVertV;
		highVertV = lowVertV;
		lowVertV = tempV;
	}

	if (highVertV->y < midVertV->y)
	{
		tempV = highVertV;
		highVertV = midVertV;
		midVertV = tempV;
	}

	// Find vectors from lowHorizV to midHorizV, from lowHorizV to highHorizV, from midHorizV to lowHorizV, and from midHorizV to highHorizV
	Vector2 leftToMiddle = (*midHorizV - *lowHorizV).normalized();
	Vector2 leftToRight = (*highHorizV - *lowHorizV).normalized();
	Vector2 middleToLeft = (*lowHorizV - *midHorizV).normalized();
	Vector2 middleToRight = (*highHorizV - *midHorizV).normalized();

	// Within the rectangle that the triangle is inscribed in, check if each point is inside the triangle
	for (int x = lowHorizV->x; x <= highHorizV->x; x++)
	{
		for (int y = lowVertV->y; y <= highVertV->y; y++)
		{
			Vector2 point(x, y);

			// if the point is inside the triangle
			if (((point - *lowHorizV) * leftToMiddle > leftToRight * leftToMiddle) &&
				((point - *lowHorizV) * leftToRight > leftToMiddle * leftToRight) &&
				((point - *midHorizV) * middleToLeft > middleToRight * middleToLeft) &&
				((point - *midHorizV) * middleToRight > middleToLeft * middleToRight))
			{
				write(point, c);
			}
		}
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