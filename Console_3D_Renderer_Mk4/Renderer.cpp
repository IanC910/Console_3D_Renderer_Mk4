#include "Renderer.h"


double Renderer::moveSpeed = 6.0 / 1000000.0;
double Renderer::turnSpeed = 1.4 / 1000000.0;
int Renderer::FOV = 90;

Observer Renderer::observer0;
double Renderer::UnitsPerRadian;
bool Renderer::initialized = false;
std::vector<Vertex*> Renderer::vertices;
std::vector<Triangle*> Renderer::triangles;

void Renderer::initRenderer(int screenWidth, int screenHeight)
{
	UnitsPerRadian = static_cast<float>(Display::width) / (FOV * PI / 180.0);

	Display::initDisplay(screenWidth, screenHeight);

	observer0 = Observer(8, 0, 0);
	observer0.horizLookAngle = PI;
	observer0.moveSpeed = moveSpeed;
	observer0.turnSpeed = turnSpeed;

	reset();

	initialized = true;
}

void Renderer::render(std::string filePath)
{
	if (!initialized)
	{
		std::cout << "Renderer not initialized";
		exit(1);
	}

	initObjectFromFile(filePath);

	titleScreen();

	Display::setBlank();

	std::list<Vector2> printedPositions; // for keeping track of vertices that have been written to S.screen

	auto timeStart = std::chrono::system_clock::now();
	auto timeEnd = timeStart;

	//  Main Loop

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		calcScreenCoords();

		//  Writing Vertices to screen array

		for (int t = 0; t < triangles.size(); t++) // for each triangle
		{
			// if the triangle is visible: face's normal dot (line of sight to the triangle) is negative
			if(triangles[t]->normal * (triangles[t]->vertices[0]->pos - observer0.pos) < 0)
			{
				for (int v = 0; v < 3; v++) // for each vertex of the triangle
				{
					// if screen position of vertex is within screen boundaries
					if (Display::isValid(triangles[t]->vertices[v]->screenPos))
					{
						Display::write(triangles[t]->vertices[v]->screenPos, '#');
						printedPositions.push_back(triangles[t]->vertices[v]->screenPos); // keep track of vertices that have been printed so validity check is no longer needed for removal
					}
				}
			}
		}

		//  Writing Controls to screen array

		writeControls();

		//  Printing screen to terminal

		Display::update();

		//  Removing Vertices from screen array

		/*while (!printedPositions.empty())
		{
			Display::write(printedPositions.front(), ' ');
			printedPositions.pop_front();
		}*/
		Display::setBlank();

		//  Checking elapsed time

		timeEnd = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
		timeStart = std::chrono::system_clock::now();

		//  observer0 Input

		observer0.GetUserInput(deltaTime);

	} // End of Main Loop

	reset();
}

void Renderer::initObjectFromFile(std::string filePath)
{
	vertices.clear();
	triangles.clear();

	std::ifstream inFile(filePath);
	std::string line;
	std::string strX, strY, strZ;
	float floX, floY, floZ;

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

		if (line == "")
			continue;

		std::getline(inString, strX, ',');
		std::getline(inString, strY, ',');
		std::getline(inString, strZ, '#');

		floX = atof(strX.c_str());
		floY = atof(strY.c_str());
		floZ = atof(strZ.c_str());

		vertices.push_back(new Vertex(floX, floY, floZ));
	}

	// Read vertex triplets for triangles

	std::getline(inFile, line); // Skip the blank line and header
	std::getline(inFile, line);

	std::string sVertex1, sVertex2, sVertex3; // string representations of the vertex indices
	int nVertex1, nVertex2, nVertex3; // Vertex indices in the vertices list

	while (std::getline(inFile, line) && line != "END")
	{
		std::istringstream inString(line);

		if (line == "")
			continue;

		std::getline(inString, sVertex1, ',');
		std::getline(inString, sVertex2, ',');
		std::getline(inString, sVertex3, '#');

		nVertex1 = atof(sVertex1.c_str());
		nVertex2 = atof(sVertex2.c_str());
		nVertex3 = atof(sVertex3.c_str());

		// Create Triangles

		triangles.push_back(new Triangle(vertices[nVertex1], vertices[nVertex2], vertices[nVertex3]));
	}

	inFile.close();
}

void Renderer::calcScreenCoords()
{
	Vector3 ObsToP; // vector from observer0.pos to a vertex
	Vector3 pVert; // Projection of ObsToP onto the vertical plane that the observer's line of sight goes through
	Vector3 pHoriz; // Projection of ObsToP onto HPlane
	Vector3 nVPlane; // Normal to the vertical plane: perpendicular to the user's line of sight, and whose z component is 0
	Vector3 nHPlane; // Normal to HPlane: perpendicular to observer0.pos and nVPlane. Note: HPlane is not actually horizontal

	for (int i = 0; i < vertices.size(); i++)
	{
		// project vector ObsToP onto vertical and horizontal planes to get angles

		ObsToP = vertices[i]->pos - observer0.pos;

		nVPlane.set(observer0.lineOfSight.y, -observer0.lineOfSight.x, 0); // Right Rotation of observer0.lineOfSight (with z = 0) clockwise. Direction is important for finding nHPlane
		nHPlane = nVPlane.cross(observer0.lineOfSight); // order is important. nHPlane must be pointing up (z > 0). Note: HPlane is not actually horizontal

		pVert = ObsToP - ObsToP.projOnto(nVPlane); // Project ObsToP onto the vertical plane
		pHoriz = ObsToP - ObsToP.projOnto(nHPlane); // Project ObsToP onto HPlane


		// Dot product formula rearranged to isolate the angle
		// multiply x and divide y by sqrt(2) for scaling (in the terminal, the characters are ~2x as tall as they are wide)

		vertices[i]->screenPos.y = static_cast<int>(acos(pVert * observer0.lineOfSight / (pVert.abs() * observer0.lineOfSight.abs())) * UnitsPerRadian) / sqrt(2.0);
		vertices[i]->screenPos.x = static_cast<int>(acos(pHoriz * observer0.lineOfSight / (pHoriz.abs() * observer0.lineOfSight.abs())) * UnitsPerRadian) * sqrt(2.0);
		

		// Note: At this point, the screen position components are positive by default because of acos()
		// The following if-statements use the normal vectors to the vertical plane and HPlane to determine where on the screen the vertex should be:

		if (vertices[i]->pos * nHPlane < observer0.pos * nHPlane) // if the vertex is in the bottom half of the screen
			vertices[i]->screenPos.y *= -1;

		if (vertices[i]->pos * nVPlane < observer0.pos * nVPlane) // if the vertex is in the left half of the screen
			vertices[i]->screenPos.x *= -1;

		vertices[i]->screenPos.x += Display::width / 2;
		vertices[i]->screenPos.y += Display::height / 2;
	}
}

void Renderer::writeControls()
{
	Display::write(Vector2(1, Display::height - 1), "Use W, A, S, and D to move in the horizontal plane.");
	Display::write(Vector2(1, Display::height - 2), "Use SPACE and CTRL to move vertically.");
	Display::write(Vector2(1, Display::height - 3), "Use Arrow Keys to Look Around.");
	Display::write(Vector2(1, Display::height - 4), "Press ESC to exit the program.");
}

void Renderer::titleScreen()
{
	Display::write(Vector2(Display::width / 2.0f - 8, Display::height / 2.0f), "3D Renderer Mk3");
	Display::write(Vector2(Display::width / 2.0f - 10, Display::height / 2.0f - 1), "Press Space to Start");
	Display::update();

	while (!GetAsyncKeyState(VK_SPACE))
	{ /* Wait for Space to be pressed */ }
}

void Renderer::reset()
{
	// Delete all triangles
	for (int t = 0; t < triangles.size(); t++) // for each triangle
	{
		delete triangles[t];
		triangles[t] = nullptr;
	}

	triangles.clear();

	// Delete all vertices
	for (int v = 0; v < vertices.size(); v++) // for each vertex
	{
		delete vertices[v];
		vertices[v] = nullptr;
	}

	vertices.clear();
}