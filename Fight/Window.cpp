#include "Window.h"

Window::Window(const char *windowName, int screenWidth, int screenHeight, unsigned int currentFlags) 
{
	//The pixel screen height and width.
	n_screenWidth = screenWidth;
	n_screenHeight = screenHeight;

	//Sets default flags.
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_ALLOW_HIGHDPI;

	//Some extra flag options.
	if (currentFlags & INVISABLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	//Creates a openGL window using the user variables.
	n_sdlWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, n_screenWidth, n_screenHeight, flags);

	//Checks if the window is there.
	if (n_sdlWindow == nullptr) {
		printf("Window Error");
	}

	//Creates the glContext using the window.
	SDL_GLContext glContext = SDL_GL_CreateContext(n_sdlWindow);

	//Checks if the context was created.
	if (glContext == nullptr) {
		printf("GL context Error");
	}

	//Starts glew and gets the error message.
	GLenum error = glewInit();
	
	//Checks glew was init properly.
	if (error != GLEW_OK) {
		printf("Glew Error");
	}

	//Prints the version.
	printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

	//The background clear color to black.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Vsync locks screen to the computer screen hrtz.
	SDL_GL_SetSwapInterval(1);

	//Blending setting.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Amount of samples and sample settings.
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	//Only renders forward facing objects.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Depth testing.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

Window::~Window()
{
}

/*
	Switches to the next screen.
*/
void Window::swapBuffer()
{
	//Renders next screen
	SDL_GL_SwapWindow(n_sdlWindow);
}