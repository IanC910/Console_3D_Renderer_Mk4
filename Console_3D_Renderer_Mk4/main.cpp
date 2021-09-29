
#include <string>

#include "Renderer.h"

void run();

// Tests
void testDrawTriangle();

int main()
{
	run();

	return 0;
}

void run()
{
	std::string objectFiles[] = { "..\\Objects\\Cube.txt", "..\\Objects\\Sphere.txt" };

	Renderer::initRenderer(213, 50); // My local terminal fullscreen = 213 (width) x 50 (height)
	Renderer::render(objectFiles[0]);
	Renderer::render(objectFiles[1]);
}

void testDrawTriangle()
{
	Debug::logInfo("testDrawTriangle", "Starting Test");

	wchar_t fillChar = 0x2588;

	Display::initDisplay(213, 50);

	Debug::logInfo("testDrawTriangle", "Drawing triangle 0...");
	Vector2 vec0(20, 20);
	Vector2 vec1(40, 20);
	Vector2 vec2(50, 30);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Debug::logInfo("testDrawTriangle", "Drawing triangle 1...");
	vec0.set(70, 20);
	vec1.set(70, 40);
	vec2.set(80, 25);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Debug::logInfo("testDrawTriangle", "Drawing triangle 2...");
	vec0.set(100, 20);
	vec1.set(100, 30);
	vec2.set(100, 40);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Debug::logInfo("testDrawTriangle", "Drawing triangle 3...");
	vec0.set(120, 40);
	vec1.set(125, 30);
	vec2.set(150, 20);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Display::update();

	while (!GetAsyncKeyState(VK_ESCAPE)) {}
}

