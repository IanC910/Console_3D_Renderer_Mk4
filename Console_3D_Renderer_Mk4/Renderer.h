/*
3D Object Terminal Renderer
By: Ian Cruikshank

Note: This program uses the Windows.h library, so it can only be run on windows machines

Controls are displayed on screen

There are only 2 main methods available to the user: render and initRenderer.
initRenderer must be called prior to render, and its arguments are the dimensions of the terminal in which it displays
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "Common.h"

#include "Display.h"
#include "Vertex.h"
#include "Triangle.h"
#include "Observer.h"

class Renderer
{
public:

	static void render(std::string filePath);
	// Renders the object in the object text file at filePath

	static void initRenderer(int screenWidth, int screenHeight);
	// This must be called once before rendering
	// Enter the desired dimensions of the screen as arguements


private:
	
	static double moveSpeed; // Move Speed in Units per Microsecond
	static double turnSpeed; // Turning Speed in Radians per mircosecond
	static int FOV; // Field of View in Degrees

	static Observer observer0;
	static std::string objectName;
	static double UnitsPerRadian;
	static bool initialized;
	static std::vector<Vertex*> vertices;
	static std::vector<Triangle*> triangles;

	Renderer(); // Private Constructor so class cannot be instantiated
	static void initObjectFromFile(std::string filePath);
	static void calcScreenCoords();
	static void writeControls();
	static void titleScreen();
	static void reset();

};

#endif
