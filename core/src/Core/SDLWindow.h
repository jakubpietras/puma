#pragma once
#include <SDL3/SDL.h>
#include "Core/Core.h"

namespace kb
{
	class SDLWindow
	{
	public:
		SDLWindow(int width = 1920, int height = 1080);
		~SDLWindow();
		void SwapBuffers();
		inline SDL_Window* GetHandle() { return m_WHandle; }
		inline SDL_GLContext GetContext() { return m_Context; }
	private:
		SDL_Window* m_WHandle;
		SDL_GLContext m_Context;
		int m_ScrWidth, m_ScrHeight;
	};
}


