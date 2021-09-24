#include <math.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <ctime>

#include "Screen.hpp"
#include "Vertex.hpp"
#include "Vector3D.hpp"
#include "Vector2D.hpp"
#include "Renderer.hpp"


double Renderer::moveSpeed = 6.0 / 1000000.0;
double Renderer::turnSpeed = 1.4 / 1000000.0;
int Renderer::FOV = 90;

Screen* Renderer::S;
Observer Renderer::User;
double Renderer::UnitsPerRadian;
bool Renderer::initialized = false;
std::vector<Vertex> Renderer::vertices;

void Renderer::initRenderer(int screenWidth, int screenHeight)
{
	S = new Screen(screenWidth, screenHeight);
	UnitsPerRadian = static_cast<float>(S->width) / (FOV * pi / 180.0);

	S->startScreen();
	S->setBlank();

	User = Observer(8, 0, 0);
	User.horizAngle = pi;

	initialized = true;
}

void Renderer::render(std::string filePath)
{
	if (!initialized)
	{
		std::cout << "Renderer not initialized";
		exit(1);
	}

	initVerticesFromFile(filePath);

	startupScreen();

	S->setBlank();

	std::queue<Vector2D> QVertexScreenPos; // for keeping track of vertices that have been written to S.screen

	auto timeStart = std::chrono::system_clock::now();
	auto timeEnd = timeStart;

	// ======================================================================== Main Loop

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		calcScreenCoords();

		// ======================================================================== Writing Vertices to screen array

		for (int n = vertices.size() - 1; n >= 0; n--)
		{
			// check if screen position of vertex is within screen boundaries
			if (S->isValid(vertices[n].screenPos))
			{
				S->write(vertices[n].screenPos, vertices[n].appearance);
				QVertexScreenPos.push(vertices[n].screenPos); // keep track of vertices that have been printed so validity check is no longer needed for removal
			}
		}

		// ======================================================================== Writing Controls to screen array

		writeControls();

		// ======================================================================== Printing screen to terminal

		S->update();

		// ======================================================================== Removing Vertices from screen array

		while (!QVertexScreenPos.empty())
		{
			S->write(QVertexScreenPos.front(), ' ');
			QVertexScreenPos.pop();
		}

		// ======================================================================== Checking elapsed time

		timeEnd = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
		timeStart = std::chrono::system_clock::now();

		// ======================================================================== User Input

		User.GetUserInput(moveSpeed, turnSpeed, deltaTime);

	} // End of Main Loop
}

void Renderer::initVerticesFromFile(std::string filePath)
{
	vertices.clear();

	std::ifstream inFile(filePath);
	std::string line;
	std::string inX, inY, inZ;
	float fX, fY, fZ;

	if (!inFile.is_open())
	{
		std::cout << "\n\nERROR: Couldn't open Object File\n\n";
		exit(1);
	}

	std::getline(inFile, line); // Skip the header

	// Read vertices

	while (std::getline(inFile, line) && line != "END")
	{
		std::istringstream inString(line);

		std::getline(inString, inX, ',');
		std::getline(inString, inY, ',');
		std::getline(inString, inZ, '#');

		fX = atof(inX.c_str());
		fY = atof(inY.c_str());
		fZ = atof(inZ.c_str());

		vertices.push_back(Vertex(fX, fY, fZ));
	}

	// Read vertex pairs for lines

	std::getline(inFile, line); // Skip the blank line and header
	std::getline(inFile, line);

	std::string inV1, inV2;
	int nV1, nV2;
	float mX, mY, mZ;
	double incr;

	while (std::getline(inFile, line) && line != "END")
	{
		std::istringstream inString(line);

		std::getline(inString, inV1, ',');
		std::getline(inString, inV2, '#');

		nV1 = atof(inV1.c_str());
		nV2 = atof(inV2.c_str());

		// Create Line of vertices

		Vector3D m(vertices[nV1].pos.x - vertices[nV2].pos.x, vertices[nV1].pos.y - vertices[nV2].pos.y, vertices[nV1].pos.z - vertices[nV2].pos.z);

		incr = 0.2 / m.abs();

		for (float t = incr; t < 1.0 - incr / 2.0; t += incr)
		{
			vertices.push_back(Vertex(m.x * t + vertices[nV2].pos.x, m.y * t + vertices[nV2].pos.y, m.z * t + vertices[nV2].pos.z, '-'));
		}
	}

	inFile.close();
}

void Renderer::calcScreenCoords()
{
	Vector3D ObsToP; // vector from User.pos to a vertex
	Vector3D pVert; // Projection of ObsToP onto the vertical plane that the observer's line of sight goes through
	Vector3D pHoriz; // Projection of ObsToP onto HPlane
	Vector3D nVPlane; // Normal to the vertical plane: perpendicular to the user's line of sight, and whose z component is 0
	Vector3D nHPlane; // Normal to HPlane: perpendicular to User.pos and nVPlane. Note: HPlane is not actually horizontal

	for (int n = 0; n < vertices.size(); n++)
	{
		// project vector ObsToP onto vertical and horizontal planes to get angles

		ObsToP = vertices[n].pos - User.pos;

		nVPlane.set(User.LOS.y, -User.LOS.x, 0); // Right Rotation of User.LOS (with z = 0) clockwise. Direction is important for finding nHPlane
		nHPlane = nVPlane.cross(User.LOS); // order is important. nHPlane must be pointing up (z > 0). Note: HPlane is not actually horizontal

		pVert = ObsToP - ObsToP.projOnto(nVPlane); // Project ObsToP onto the vertical plane
		pHoriz = ObsToP - ObsToP.projOnto(nHPlane); // Project ObsToP onto HPlane


		// Dot product formula rearranged to isolate the angle
		// multiply x and divide y by sqrt(2) for scaling (in the terminal, the characters are ~2x as tall as they are wide)

		vertices[n].screenPos.y = static_cast<int>(acos(pVert * User.LOS / (pVert.abs() * User.LOS.abs())) * UnitsPerRadian) / sqrt(2.0);
		vertices[n].screenPos.x = static_cast<int>(acos(pHoriz * User.LOS / (pHoriz.abs() * User.LOS.abs())) * UnitsPerRadian) * sqrt(2.0);
		

		// Note: At this point, the screen position components are positive by default because of acos()
		// The following if-statements use the normal vectors to the vertical plane and HPlane to determine where on the screen the vertex should be:

		if (vertices[n].pos * nHPlane < User.pos * nHPlane) // if the vertex is in the bottom half of the screen
			vertices[n].screenPos.y *= -1;

		if (vertices[n].pos * nVPlane < User.pos * nVPlane) // if the vertex is in the left half of the screen
			vertices[n].screenPos.x *= -1;

		vertices[n].screenPos.x += S->width / 2;
		vertices[n].screenPos.y += S->height / 2;
	}
}

void Renderer::writeControls()
{
	S->writeString(Vector2D(1, S->height - 1), "Use W, A, S, and D to move in the horizontal plane.");
	S->writeString(Vector2D(1, S->height - 2), "Use SPACE and CTRL to move vertically.");
	S->writeString(Vector2D(1, S->height - 3), "Use Arrow Keys to Look Around.");
	S->writeString(Vector2D(1, S->height - 4), "Press ESC to exit the program.");
}

void Renderer::startupScreen()
{
	S->writeString(Vector2D(S->width / 2.0f - 8, S->height / 2.0f), "3D Renderer Mk3");
	S->writeString(Vector2D(S->width / 2.0f - 10, S->height / 2.0f - 1), "Press Space to Start");
	S->update();

	while (!GetAsyncKeyState(VK_SPACE))
	{ /* Wait for Space to be pressed */ }
}