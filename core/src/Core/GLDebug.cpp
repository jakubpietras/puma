#include "GLDebug.h"
#include <glad/glad.h>
#include "Core/Log.h"
#include <iostream>

namespace kb
{
	static void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, unsigned int id,
		GLenum severity, GLsizei length,
		const char* message, const void* userParam)
	{
		// Ignore notifications
		if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

		// Formatting of errors
		const char* typeStr = (type == GL_DEBUG_TYPE_ERROR) ? "** GL ERROR **" : "GL DEBUG";

		if (type == GL_DEBUG_TYPE_ERROR)
		{
			P_ERROR("{0}: {1}", typeStr, message);

#ifdef _DEBUG
	// __debugbreak() dla MSVC, __builtin_trap() dla GCC/Clang
#ifdef _MSC_VER
			__debugbreak();
#else
			__builtin_trap();
#endif
#endif
		}
		else
		{
			P_WARN("{0}: {1}", typeStr, message);
		}
	}

	void EnableOpenGLDebug()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		P_INFO("OpenGL Debugging Enabled");
	}

}