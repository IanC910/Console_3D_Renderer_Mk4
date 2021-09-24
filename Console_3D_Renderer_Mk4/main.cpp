
#include <string>

#include "Renderer.hpp"

int main()
{
	// This is a sample main function

	std::string objectFiles[] = { "Objects\\Cube.txt", "Objects\\Sphere.txt" };

	Renderer::initRenderer(213, 50); // My local terminal fullscreen = 213 (width) x 50 (height)
	Renderer::render(objectFiles[0]);
	Renderer::render(objectFiles[1]);

	return 0;
}