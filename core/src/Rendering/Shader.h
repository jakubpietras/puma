#pragma once
#include "Core/Core.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include <vector>
#include <string>
#include "armath.h"

namespace kb
{
	class Shader
	{
	public:
		Shader(const std::string& vsPath,
			const std::string& fsPath,
			const std::string& tcsPath = "",
			const std::string& tesPath = "");
		~Shader();
		void Use() const;
		void SetVec2(const std::string& name, const float value[2]) const;
		void SetVec3(const std::string& name, const kbm::Vec3& value) const;
		void SetMat4(const std::string& name, const kbm::Mat4& value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetBool(const std::string& name, bool value) const;
		void SetUInt(const std::string& name, u32 value) const;

	protected:
		std::string LoadSource(const std::string& path);
		uint32_t CompileShader(GLuint shaderType, const std::string& shaderSource);
		void LinkProgram(std::vector<GLuint>& shaders);
		void DeleteShaders(std::vector<GLuint>& shaders);
	private:
		GLuint m_programID;
	};

	class ShaderLib
	{
	public:
		static void Init();
		static std::shared_ptr<Shader> Get(const std::string& name);

	private:
		static std::unordered_map<std::string, std::shared_ptr<Shader>> s_Shaders;
	};
}

