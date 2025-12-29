#include "SDLWindow.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include "Core/GLDebug.h"

namespace kb
{
	SDLWindow::SDLWindow(int width /*= SCR_WIDTH_INIT*/, int height /*= SCR_HEIGHT_INIT*/)
		: m_ScrWidth(width), m_ScrHeight(height)
	{
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
			if (!SDL_Init(SDL_INIT_VIDEO)) {
				P_ERROR("Failed to initialize SDL: {0}", SDL_GetError());
				return;
			}
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG); // for debugging

		m_WHandle = SDL_CreateWindow("PUMA", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!m_WHandle) {
			P_ERROR("Failed to create a window: {0}", SDL_GetError());
			return;
		}

		m_Context = SDL_GL_CreateContext(m_WHandle);
		if (!m_Context) {
			P_ERROR("Failed to create OpenGL context: {0}", SDL_GetError());
			return;
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			P_ERROR("Failed to initialize GLAD");
			return;
		}

		// OpenGL debugging
		EnableOpenGLDebug();

		// VSync
		SDL_GL_SetSwapInterval(0);
	}

	SDLWindow::~SDLWindow()
	{
		if (m_Context) 
			SDL_GL_DestroyContext(m_Context);
		if (m_WHandle) 
			SDL_DestroyWindow(m_WHandle);
		SDL_Quit();
	}

	void SDLWindow::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_WHandle);
	}
}