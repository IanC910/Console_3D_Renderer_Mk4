#include "Renderer.h"

double Renderer::moveSpeed = 6.0 / 1000000.0;
double Renderer::turnSpeed = 1.4 / 1000000.0;
int Renderer::FOV = 90;

bool Renderer::quit = 0;

Observer Renderer::observer0;
std::string Renderer::objectName = "";
double Renderer::UnitsPerRadian;
bool Renderer::initialized = false;
std::vector<Vertex*> Renderer::vertices;
std::vector<Triangle*> Renderer::triangles;

// Lightest to darkest shades in inverted console colours
wchar_t lightShade		= 0x2588; // lightest
wchar_t medLightShade	= 0x2593;
wchar_t medDarkShade	= 0x2592;
wchar_t darkShade		= 0x2591; // darkest

void Renderer::initRenderer(int screenWidth, int screenHeight)
{
	Debug::info("Renderer", "Initializing Renderer...");

	UnitsPerRadian = Display::width / (FOV * PI / 180.0);

	Display::initDisplay(screenWidth, screenHeight);

	observer0 = Observer(8, 0, 0);
	observer0.horizLookAngle = PI;

	reset();

	initialized = true;

	Debug::info("Renderer", "Renderer Initialized");
}

void Renderer::render(std::string filePath)
{
	if (!initialized)
	{
		Debug::error("Renderer", "Attempted to render an object when renderer not initialized");
		exit(1);
	}

	initObjectFromFile(filePath);

	Debug::info("Renderer", "Starting render of object \"" + objectName + "\"");

	titleScreen();

	Display::setBlank();

	auto timeStart = std::chrono::system_clock::now();
	auto timeEnd = timeStart;

	//  Main Loop
	while (!quit)
	{
		calcScreenCoords();

		drawEnvironment();

		//  Writing Controls to screen array
		writeUI();

		//  Printing screen to terminal
		Display::update();

		//  Reset screen array
		Display::setBlank();

		//  Checking elapsed time
		timeEnd = std::chrono::system_clock::now();
		long long deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
		timeStart = std::chrono::system_clock::now();

		processUserInput(deltaTime);

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
		Debug::error("Renderer", "Couldn't open object file");
		exit(1);
	}

	std::getline(inFile, objectName); // Object Name
	std::getline(inFile, line); // Skip vertices header

	Debug::info("Renderer", "Opened object file of object \"" + objectName + "\"");

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
	std::getline(inFile, line); // Skip the blank line and triangles header
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
	// Vector from observer0.pos to a vertex
	Vec3 ObsToV;

	// Position of the Vector relative to the obesrver in the observer's basis vectors, e1, e2, and e3
	Vec3 VPosInObsBasis;

	// Observer's basis vectors, follows right hand rule. These will produce a subspace of R3, consistent with the right hand rule
	Vec3 e1, e2, e3;


	// Calculate Observer's basis vectors...

	// e2 is the line of sight
	e2 = observer0.lineOfSight.normalized();
	// e1 is the line of sight rotated clockwise 90 degrees and a z component of 0
	e1 = {-e2.y, e2.x, 0};
	// e3 is e1 cross e2
	e3 = e1.cross(e2);


	for (int i = 0; i < vertices.size(); i++)
	{
		ObsToV = vertices[i]->pos - observer0.pos;

	

		/*ObsToP = vertices[i]->pos - observer0.pos;

		nVPlane.set(observer0.lineOfSight.y, -observer0.lineOfSight.x, 0); // Right Rotation of observer0.lineOfSight (with z = 0) clockwise. Direction is important for finding nHPlane
		nHPlane = nVPlane.cross(observer0.lineOfSight); // order is important. nHPlane must be pointing up (z > 0). Note: HPlane is not actually horizontal

		pVert = ObsToP - ObsToP.projOnto(nVPlane); // Project ObsToP onto the vertical plane
		pHoriz = ObsToP - ObsToP.projOnto(nHPlane); // Project ObsToP onto HPlane


		// Dot product formula rearranged to isolate the angle
		// multiply x and divide y by sqrt(2) for scaling (in the terminal, the characters are ~2x as tall as they are wide)
		vertices[i]->screenPos.y = (int)(acos(pVert * observer0.lineOfSight / (pVert.abs() * observer0.lineOfSight.abs())) * UnitsPerRadian) / sqrt(2.0);
		vertices[i]->screenPos.x = (int)(acos(pHoriz * observer0.lineOfSight / (pHoriz.abs() * observer0.lineOfSight.abs())) * UnitsPerRadian) * sqrt(2.0);
		

		// Note: At this point, the screen position components are positive by default because of acos()
		// The following if-statements use the normal vectors to the vertical plane and HPlane to determine where on the screen the vertex should be:

		if (vertices[i]->pos * nHPlane < observer0.pos * nHPlane) // if the vertex is in the bottom half of the screen
			vertices[i]->screenPos.y *= -1;

		if (vertices[i]->pos * nVPlane < observer0.pos * nVPlane) // if the vertex is in the left half of the screen
			vertices[i]->screenPos.x *= -1;

		vertices[i]->screenPos.x += Display::width / 2;
		vertices[i]->screenPos.y += Display::height / 2;

		// Cap the screen positions. Otherwise, Display::drawTriangle bugs sometimes
		if (vertices[i]->screenPos.x > Display::width + 5)
			vertices[i]->screenPos.x = Display::width + 5;
		if (vertices[i]->screenPos.x < -Display::width - 5)
			vertices[i]->screenPos.x = -Display::width - 5;
		if (vertices[i]->screenPos.y > Display::height + 5)
			vertices[i]->screenPos.y = Display::height + 5;
		if (vertices[i]->screenPos.y < -Display::height - 5)
			vertices[i]->screenPos.y = -Display::height - 5;*/
	}
}

void Renderer::drawEnvironment()
{
	//  Writing Vertices to screen array
	for (int t = 0; t < triangles.size(); t++) // for each triangle
	{
		// brightness is an indicator of how much the triangle is facing the observer
		double brightness = triangles[t]->normal() * (observer0.pos - triangles[t]->vertices[0]->pos).normalized();

		if (brightness > 0)
		{
			// Find character to draw based on given brightness
			wchar_t charToDraw;

			if (brightness > 0.75f)			charToDraw = lightShade;
			else if (brightness > 0.5f)		charToDraw = medLightShade;
			else if (brightness > 0.25f)    charToDraw = medDarkShade;
			else							charToDraw = darkShade;

			Display::drawTriangle(triangles[t]->vertices[0]->screenPos, triangles[t]->vertices[1]->screenPos, triangles[t]->vertices[2]->screenPos, charToDraw);
		}
	}
}

void Renderer::writeUI()
{
	Display::write(Vec2(1, Display::height - 1), "Use W, A, S, and D to move in the horizontal plane.");
	Display::write(Vec2(1, Display::height - 2), "Use SPACE and CTRL to move vertically.");
	Display::write(Vec2(1, Display::height - 3), "Use Arrow Keys to Look Around.");
	Display::write(Vec2(1, Display::height - 4), "Press ESC to exit the program.");

	Display::write(Vec2(Display::width / 2 - 10, Display::height - 1), "Object: " + ((objectName == "") ? "(No object name)" : objectName));
}

void Renderer::processUserInput(long long deltaTime)
{
	// W:           0x57
	// A:           0x41
	// S:           0x53
	// D:           0x44
	// LCTRL:       0xA2
	// Space:       0x20
	// Left arrow:  0x25
	// Up arrow:    0x26
	// Right arrow: 0x27
	// Down arrow:  0x28
	// Esc:         0x1B

	Vec3 directionOfMovement;

	// W: move forward
	if (GetAsyncKeyState('W'))
	{
		directionOfMovement = observer0.lineOfSight;
		directionOfMovement.z = 0;
		observer0.pos += directionOfMovement * moveSpeed * deltaTime / directionOfMovement.abs();
	}

	// S: move backward
	if (GetAsyncKeyState('S'))
	{
		directionOfMovement = observer0.lineOfSight;
		directionOfMovement.z = 0;
		observer0.pos += directionOfMovement * (-moveSpeed) * deltaTime / directionOfMovement.abs();
	}

	// A: move left
	if (GetAsyncKeyState('A')) // Move Left
	{
		directionOfMovement.set(-observer0.lineOfSight.y, observer0.lineOfSight.x, 0); // lineOfSight rotated PI/2 counter clockwise
		observer0.pos += directionOfMovement * moveSpeed * deltaTime / directionOfMovement.abs();
	}

	// D: move right
	if (GetAsyncKeyState('D')) // Move Right
	{
		directionOfMovement.set(observer0.lineOfSight.y, -observer0.lineOfSight.x, 0); // lineOfSight rotated PI/2 clockwise
		observer0.pos += directionOfMovement * moveSpeed * deltaTime / directionOfMovement.abs();
	}

	// Space: move up
	if (GetAsyncKeyState(VK_SPACE)) // Move UP
	{
		observer0.pos.z += moveSpeed * deltaTime * 0.8;
	}

	// LCTRL: move down
	if (GetAsyncKeyState(VK_LCONTROL)) // Move Down
	{
		observer0.pos.z -= moveSpeed * deltaTime * 0.8;
	}

	// Up arrow: look up
	if (GetAsyncKeyState(VK_UP) && observer0.vertLookAngle < PI / 2.0 - PI / 180.0) // Look Up
	{
		observer0.vertLookAngle += turnSpeed * deltaTime;
	}

	// Down arrow: look down
	if (GetAsyncKeyState(VK_DOWN) && observer0.vertLookAngle > -PI / 2.0 + PI / 180.0) // Look Down
	{
		observer0.vertLookAngle -= turnSpeed * deltaTime;
	}

	// Left arrow: look left
	if (GetAsyncKeyState(VK_LEFT)) // Look left
	{
		observer0.horizLookAngle += turnSpeed * deltaTime;
	}

	// Right arrow: look right
	if (GetAsyncKeyState(VK_RIGHT)) // Look Right
	{
		observer0.horizLookAngle -= turnSpeed * deltaTime;
	}

	// Escape: quit
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		quit = 1;
	}

	// Update lineOfSight
	observer0.lineOfSight.set(
		cos(observer0.horizLookAngle) * cos(observer0.vertLookAngle),
		sin(observer0.horizLookAngle) * cos(observer0.vertLookAngle),
		sin(observer0.vertLookAngle));

}

void Renderer::titleScreen()
{
	Display::write(Vec2(Display::width / 2.0f - 9, Display::height / 2.0f), "3D Console Renderer");
	Display::write(Vec2(Display::width / 2.0f - 10, Display::height / 2.0f - 1), "Rendering object \"" + objectName + "\"");
	Display::write(Vec2(Display::width / 2.0f - 10, Display::height / 2.0f - 2), "Press Space to Start");
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

	quit = 0;

	Debug::info("Renderer", "Renderer Reset");
}