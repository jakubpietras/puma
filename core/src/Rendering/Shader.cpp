#include "Shader.h"
#include <fstream>

namespace m = kbm;

namespace kb
{
	Shader::Shader(const std::string& vsPath, const std::string& fsPath, const std::string& tcsPath /*= ""*/, const std::string& tesPath /*= ""*/)
	{
		std::vector<GLuint> shaders;
		std::string vertexSource = LoadSource(vsPath),
			fragmentSource = LoadSource(fsPath);
		shaders.push_back(CompileShader(GL_VERTEX_SHADER, vertexSource));
		shaders.push_back(CompileShader(GL_FRAGMENT_SHADER, fragmentSource));
		if (!tcsPath.empty())
			shaders.push_back(CompileShader(GL_TESS_CONTROL_SHADER, LoadSource(tcsPath)));

		if (!tesPath.empty())
			shaders.push_back(CompileShader(GL_TESS_EVALUATION_SHADER, LoadSource(tesPath)));

		LinkProgram(shaders);
		DeleteShaders(shaders);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programID);
	}

	void Shader::Use() const
	{
		glUseProgram(m_programID);
	}

	void Shader::SetVec2(const std::string& name, const float value[2]) const
	{
		auto location = glGetUniformLocation(m_programID, name.c_str());
		glProgramUniform2fv(m_programID, location, 1, value);
	}

	void Shader::SetVec3(const std::string& name, const m::Vec3& value) const
	{
		auto location = glGetUniformLocation(m_programID, name.c_str());
		glProgramUniform3fv(m_programID, location, 1, value.Data());
	}

	void Shader::SetMat4(const std::string& name, const m::Mat4& value) const
	{
		auto location = glGetUniformLocation(m_programID, name.c_str());
		glProgramUniformMatrix4fv(m_programID, location, 1, GL_FALSE, value.data.data());
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		auto location = glGetUniformLocation(m_programID, name.c_str());
		glProgramUniform1i(m_programID, location, value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		auto location = glGetUniformLocation(m_programID, name.c_str());
		glProgramUniform1f(m_programID, location, value);
	}

	void Shader::SetBool(const std::string& name, bool value) const
	{
		if (value)
			SetInt(name, 1);
		else
			SetInt(name, 0);
	}

	void Shader::SetUInt(const std::string& name, uint32_t value) const
	{
		auto location = glGetUniformLocation(m_programID, name.c_str());
		glProgramUniform1ui(m_programID, location, value);
	}

	std::string Shader::LoadSource(const std::string& path)
	{
		std::ifstream istrm(path);
		if (!istrm.is_open())
			P_ERROR("Failed to open {0}", path);

		std::stringstream ss;
		ss << istrm.rdbuf();
		istrm.close();
		return ss.str();
	}

	uint32_t Shader::CompileShader(uint32_t shaderType, const std::string& shaderSource)
	{
		const char* source = shaderSource.c_str();
		auto shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, nullptr);

		glCompileShader(shader);
		char infoLog[512];
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			if (maxLength > 0)
			{
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				P_ERROR("Shader compilation failed:\n{0}", infoLog.data());
			}
			else
			{
				P_ERROR("Shader compilation failed (No details available)");
			}

			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	void Shader::LinkProgram(std::vector<uint32_t>& shaders)
	{
		m_programID = glCreateProgram();

		for (auto& shader : shaders)
			glAttachShader(m_programID, shader);

		glLinkProgram(m_programID);

		GLint status;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &status);

		if (status == GL_FALSE) {
			// Get the length of the info log
			GLint logLength;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);

			if (logLength > 0) {
				// Retrieve the info log
				std::vector<char> log(logLength);
				glGetProgramInfoLog(m_programID, logLength, nullptr, log.data());

				// Clean up the failed program
				glDeleteProgram(m_programID);
				m_programID = 0;

				// Create detailed error message
				std::string errorMsg = "Shader program linking failed:\n";
				errorMsg += std::string(log.begin(), log.end());

				P_ERROR(errorMsg);
			}
			else {
				glDeleteProgram(m_programID);
				m_programID = 0;
				P_ERROR("Shader program linking failed with no error log.");
			}
		}
	}

	void Shader::DeleteShaders(std::vector<uint32_t>& shaders)
	{
		for (auto& shader : shaders)
		{
			glDetachShader(m_programID, shader);
			glDeleteShader(shader);
		}
	}

	std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderLib::s_Shaders{};

	void ShaderLib::Init()
	{
		s_Shaders["Grid"] = std::make_shared<Shader>(
			"src/Resources/Shaders/grid.vert",
			"src/Resources/Shaders/grid.frag");
		s_Shaders["Gizmo"] = std::make_shared<Shader>(
			"src/Resources/Shaders/gizmo.vert",
			"src/Resources/Shaders/gizmo.frag");
		s_Shaders["Default"] = std::make_shared<Shader>(
			"src/Resources/Shaders/default.vert",
			"src/Resources/Shaders/default.frag");
		P_INFO("Shaders initialized.");
	}

	std::shared_ptr<Shader> ShaderLib::Get(const std::string& name)
	{
		return s_Shaders[name];
	}
}