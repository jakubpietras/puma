#pragma once
#include "magic_enum/magic_enum.hpp"
#include "imgui.h"
#include "kbmath.h"
#include "Core/Core.h"
#include "fmt/format.h"

namespace kb
{
	class UIWidget
	{
	public:
		
		template <typename T>
		static bool ComboEnum(const std::string& label, T& var)
		{
			constexpr auto names = magic_enum::enum_names<T>();

			std::vector<std::string> string_storage;
			for (auto& name : names)
				string_storage.emplace_back(name);

			std::vector<const char*> strings;
			for (auto& str : string_storage)
				strings.push_back(str.c_str());

			int current = static_cast<int>(var);
			if (ImGui::Combo(label.c_str(), &current, strings.data(), static_cast<int>(strings.size())))
			{
				var = static_cast<T>(current);
				return true;
			}
			return false;
		}

		static void TextColored(const std::string& text, ImVec4 color);

		static bool DragQuat(const std::string& label, kbm::Quat& quat);
		static bool DragVec3(const char* label, kbm::Vec3& value, std::vector<std::string> labels, float min, float max);
		static bool DragUInt(const std::string& label, u32& value, u32 min, u32 max);
		static bool EditQuat(const char* label, kbm::Quat& values, float resetValue = 0.0f);
		static bool EditFloat3(const char* label, kbm::Vec3& value, std::vector<std::string> labels, float min, float max);
	};
}