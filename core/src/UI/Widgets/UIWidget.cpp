#include "UIWidget.h"

namespace kb
{

	void UIWidget::TextColored(const std::string& text, ImVec4 color)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::TextUnformatted(text.c_str());
		ImGui::PopStyleColor();
	}

	bool UIWidget::DragQuat(const std::string& label, kbm::Quat& quat)
	{
		bool committed = false;

		TextColored("W: ", ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "qw").c_str(), &quat.w, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		TextColored("X: ", ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "qx").c_str(), &quat.x, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		TextColored("Y: ", ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "qy").c_str(), &quat.y, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		TextColored("Z: ", ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "qz").c_str(), &quat.z, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		return committed;
	}

	bool UIWidget::DragVec3(const char* label, kbm::Vec3& value, std::vector<std::string> labels, float min, float max)
	{
		bool committed = false;

		TextColored(fmt::format("{}: ", labels[0]), ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "px").c_str(), &value.x, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		TextColored(fmt::format("{}: ", labels[1]), ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "py").c_str(), &value.y, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		TextColored(fmt::format("{}: ", labels[2]), ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat(fmt::format("##{}{}", label, "pz").c_str(), &value.z, 0.1f, 0.0f))
			committed = true;
		ImGui::PopItemWidth();

		return committed;
	}

	bool UIWidget::DragUInt(const std::string& label, u32& value, u32 min, u32 max)
	{
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U32, &value, 1.f, &min, &max);
	}

	bool UIWidget::EditQuat(const char* label, kbm::Quat& values, float resetValue)
	{
		ImGui::PushID(label);

		float width = (ImGui::GetContentRegionAvail().x - 4 * ImGui::GetStyle().ItemSpacing.x) / 4.0f;
		bool valueCommitted = false;

		auto DrawField = [&](const char* id, float& val, const ImVec4& color)
			{
				ImGui::PushItemWidth(width);

				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextUnformatted(id);
				ImGui::PopStyleColor();

				ImGui::SameLine();
				std::string hiddenLabel = std::string("##") + id;
				ImGui::DragFloat(hiddenLabel.c_str(), &val, 0.01f);
				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					valueCommitted = true;
				}

				ImGui::PopItemWidth();
			};

		DrawField("X", values.x, ImVec4(0.8f, 0.1f, 0.15f, 1.0f)); ImGui::SameLine();
		DrawField("Y", values.y, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));  ImGui::SameLine();
		DrawField("Z", values.z, ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); ImGui::SameLine();
		DrawField("W", values.w, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));

		ImGui::SameLine();
		ImGui::TextUnformatted(label);

		ImGui::PopID();
		return valueCommitted;
	}

	

	bool UIWidget::EditFloat3(const char* label, kbm::Vec3& value,
		std::vector<std::string> labels, float min, float max)
	{
		ImGui::PushID(label);

		float width = (ImGui::GetContentRegionAvail().x - 3 * ImGui::GetStyle().ItemSpacing.x) / 4.0f;

		bool valueChanged = false;

		auto DrawField = [&](const char* id, float& val, const ImVec4& color)
			{
				ImGui::PushItemWidth(width);

				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextUnformatted(id);
				ImGui::PopStyleColor();

				ImGui::SameLine();
				std::string hiddenLabel = std::string("##") + id;
				if (ImGui::DragFloat(hiddenLabel.c_str(), &val, 0.01f, min, max))
				{
					valueChanged = true;
				}

				ImGui::PopItemWidth();
			};

		DrawField(labels[0].c_str(), value.x, ImVec4(0.8f, 0.1f, 0.15f, 1.0f)); ImGui::SameLine();
		DrawField(labels[1].c_str(), value.y, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));  ImGui::SameLine();
		DrawField(labels[2].c_str(), value.z, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));

		ImGui::SameLine();
		ImGui::TextUnformatted(label);

		ImGui::PopID();

		return valueChanged;
	}

}