
#include "Display.h"

int Display::width = 120;
int Display::height = 35;

wchar_t* Display::screenArray = nullptr;
DWORD Display::bytesWritten;
HANDLE Display::consoleHandle;

void Display::initDisplay(int initWidth, int initHeight)
{
	Debug::info("Display", "Initializing Display...");

	width = initWidth;
	height = initHeight;

	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screenArray = new wchar_t[width * height];
	bytesWritten = 0;
	consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleHandle);

	setBlank();

	Debug::info("Display", "Display Initialized");
}

void Display::update()
{	
	// The following chunk of code was derived from https://www.youtube.com/watch?v=xW8skO7MFYw
	screenArray[width * height - 1] = '\0';
	WriteConsoleOutputCharacter(consoleHandle, screenArray, width * height, {0, 0}, &bytesWritten);
}

void Display::write(int x, int y, wchar_t c)
{
	if(isValid(Vec2(x, y)))
		screenArray[width * (height - y - 1) + x] = c;
}

void Display::write(Vec2 pos, wchar_t c)
{
	if(isValid(pos))
		screenArray[width * (height - static_cast<int>(pos.y) - 1) + static_cast<int>(pos.x)] = c;
}

void Display::write(Vec2 pos, std::string s)
{
	for (int n = 0; n < s.size(); n++)
	{
		if(isValid(Vec2(pos)))
			screenArray[width * (height - static_cast<int>(pos.y) - 1) + static_cast<int>(pos.x + n)] = s[n];
	}
}

void Display::drawTriangle(Vec2 vertex0, Vec2 vertex1, Vec2 vertex2, wchar_t fillChar)
{
	/*// Draw only Vertices
	write(vertex0, '0');
	write(vertex1, '1');
	write(vertex2, '2');
	return;*/

	// If all vertices are in the same horizontal position, the triangle has no area: no need to draw anything
	if (vertex0.x == vertex1.x && vertex1.x == vertex2.x)
		return;

	// If all vertices are in the same vertical position, the triangle has no area: no need to draw anything
	if (vertex0.y == vertex1.y && vertex1.y == vertex2.y)
		return;


	Vec2* leftV = &vertex0; // point with lowest x
	Vec2* middleV = &vertex1;
	Vec2* rightV = &vertex2; // point with greatest x

	// Sort vertices of triangle by position in the 2D screen plane
	Vec2* tempV; // for swapping purposes

	// Sort by horizontal position
	if(middleV->x < leftV->x)
	{
		tempV		= middleV;
		middleV		= leftV;
		leftV		= tempV;
	}

	if (rightV->x < leftV->x)
	{
		tempV		= rightV;
		rightV		= leftV;
		leftV		= tempV;
	}

	if (rightV->x < middleV->x)
	{
		tempV		= rightV;
		rightV		= middleV;
		middleV		= tempV;
	}

	if (leftV->x == middleV->x && middleV->y < leftV->y) // if leftV and middleV occupy the same vertical line, make middleV the higher vertex by default
	{
		Vec2* temp = middleV;
		middleV = leftV;
		leftV = temp;
	}

	if (middleV->x == rightV->x && middleV->y < rightV->y) // if middleV and rightV occupy the same vertical line, make middleV the higher vertex by default
	{
		Vec2* temp = middleV;
		middleV = rightV;
		rightV = temp;
	}

	// Find the equations of the lines from leftV to middleV, leftV to rightV, and middleV to leftV

	double leftToRightSlope = (rightV->y - leftV->y) / (rightV->x - leftV->x);

	double upperLineSlope = 0;
	double lowerLineSlope = 0;
	
	// Fill part of triangle left of the middle vertex
	if (leftV->x != middleV->x)
	{
		double leftToMiddleSlope = (middleV->y - leftV->y) / (middleV->x - leftV->x);

		if (atan(leftToMiddleSlope) > atan(leftToRightSlope))
		{
			upperLineSlope = leftToMiddleSlope;
			lowerLineSlope = leftToRightSlope;
		}
		else if (atan(leftToMiddleSlope) < atan(leftToRightSlope))
		{
			upperLineSlope = leftToRightSlope;
			lowerLineSlope = leftToMiddleSlope;
		}
		else // slopes are the same, triangle has no area, nothing to draw
		{
			return;
		}

		for (int x = ceil(leftV->x); x < middleV->x; x++)
		{
			// y = m(x - x0) + y0
			int upperYBound = floor(upperLineSlope * ((double)x - (double)leftV->x) + (double)leftV->y);
			int lowerYBound = ceil(lowerLineSlope * ((double)x - (double)leftV->x) + (double)leftV->y);

			for (int y = lowerYBound; y <= upperYBound; y++)
			{
				write(x, y, fillChar);
			}
		}
	}
	
	// Fill part of triangle right of the middle vertex
	if (middleV->x != rightV->x)
	{
		double middleToRightSlope = (rightV->y - middleV->y) / (rightV->x - middleV->x);

		if (atan(middleToRightSlope) < atan(leftToRightSlope))
		{
			upperLineSlope = middleToRightSlope;
			lowerLineSlope = leftToRightSlope;
		}
		else if (atan(middleToRightSlope) > atan(leftToRightSlope))
		{ 
			upperLineSlope = leftToRightSlope;
			lowerLineSlope = middleToRightSlope;
		}
		else // slopes are the same, triangle has no area, nothing to draw
		{
			return;
		}

		for (int x = ceil(middleV->x); x < rightV->x; x++)
		{
			// y = m(x - x0) + y0
			int upperYBound = floor(upperLineSlope * ((double)x - (double)rightV->x) + (double)rightV->y);
			int lowerYBound = ceil(lowerLineSlope * ((double)x - (double)rightV->x) + (double)rightV->y);

			for (int y = lowerYBound; y <= upperYBound; y++)
			{
				write(x, y, fillChar);
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

bool Display::isValid(Vec2 P)
{
	return ((P.y < height) && (P.y > 0) && (P.x < width) && (P.x > 0));
}