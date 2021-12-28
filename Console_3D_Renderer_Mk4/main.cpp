
#include <string>

#include "Renderer.h"

void run();

// Tests
void testDrawTriangle();
void testSetVectorWithArray();
void testMatrixAssignment();
void testMatrixMultiply();
void testMatrix3x3Inverse();

int main()
{
	run();

	// testMatrix3x3Inverse();

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
	Debug::info("testDrawTriangle", "Starting Test");

	wchar_t fillChar = 0x2588;

	Display::initDisplay(213, 50);

	Debug::info("testDrawTriangle", "Drawing triangle 0...");
	Vec2 vec0(20, 20);
	Vec2 vec1(40, 20);
	Vec2 vec2(50, 30);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Debug::info("testDrawTriangle", "Drawing triangle 1...");
	vec0.set(70, 20);
	vec1.set(70, 40);
	vec2.set(80, 25);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Debug::info("testDrawTriangle", "Drawing triangle 2...");
	vec0.set(100, 20);
	vec1.set(100, 30);
	vec2.set(100, 40);
	Display::drawTriangle(vec0, vec1, vec2, fillChar);
	Display::write(vec0, '0');
	Display::write(vec1, '1');
	Display::write(vec2, '2');

	Debug::info("testDrawTriangle", "Drawing triangle 3...");
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

void testSetVectorWithArray()
{
	Vec2 v2 = {3, 4};
	Vec3 v3 = {1, 2, 3};

	std::cout << v2.x << " " << v2.y << "\n";
	std::cout << v3.x << " " << v3.y << " " << v3.z << "\n";

	v2 = {7, 8};
	v3 = {12, 15, 17};

	std::cout << v2.x << " " << v2.y << "\n";
	std::cout << v3.x << " " << v3.y << " " << v3.z << "\n";
}

void testMatrixAssignment()
{
	Matrix m0(3, 3);

	m0.set0();

	m0[1][2] = 5;

	std::cout << m0[1][2] << "\n";

	Matrix m1(5, 5);
	m1 = m0;

	std::cout << m1[1][2] << "\n";

	m0[1][2] = 3;

	// This should still be 5
	std::cout << m1[1][2] << "\n";
}

void testMatrixMultiply()
{
	Matrix a(3, 3);
	Matrix b(3, 2);

	// Set a
	for (int i = 0; i < 9; i++)
		a[i / 3 + 1][i % 3 + 1] = i;

	std::cout << "a:\n";
	a.print();

	// Set b
	for (int i = 0; i < 6; i++)
		b[i / 2 + 1][i % 2 + 1] = 4 - i;

	std::cout << "b:\n";
	b.print();

	Matrix prod = a * b;

	std::cout << "prod\n";
	prod.print();

	// The result should be {{2, -1}, {20, 8}, {38, 17}}
}

void testMatrix3x3Inverse()
{
	Matrix3x3 m0;

	// set m0
	for (int i = 0; i < 9; i++)
	{
		m0[i / 3 + 1][i % 3 + 1] = (8 - i) * (7 - i);
	}

	m0.print();

	std::cout << "\n";

	Matrix3x3 m1 = m0.inverse();

	m1.print();
}

