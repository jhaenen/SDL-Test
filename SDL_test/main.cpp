#include <iostream>

#include <GL/glew.h>
#include <SDL/SDL.h>

bool loopActive = true;

void sdlDie(const char* message) {
	std::cout << message << std::endl;
	SDL_Quit();
	exit(1);
}

int main(int argc, char* charv[]) {
	SDL_Window* window;
	SDL_GLContext ctx;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) sdlDie("Unable to initialize SDL!");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) sdlDie("Unable to create SDL window!");

	ctx = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(1);

	while (loopActive) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) loopActive = false;
		}

		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}