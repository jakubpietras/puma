#include "Core/Log.h"
#include "Core/SDLWindow.h"
#include "Core/Application.h"

int main()
{
	kb::Log::Init();

	auto app = kb::Application();
	app.Run();

	return 0;
}