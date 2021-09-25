
#include <string>

#include "Renderer.h"

void run();

// Tests
void testDrawTriangle();

int main()
{
	testDrawTriangle();

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
	Display::initDisplay(213, 50);

	Vector2 vec0(20, 20);
	Vector2 vec1(40, 20);
	Vector2 vec2(50, 30);

	Display::drawTriangle(vec0, vec1, vec2, 0x2588);

	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Display::update();

	while (!GetAsyncKeyState(VK_ESCAPE)) {}
}

