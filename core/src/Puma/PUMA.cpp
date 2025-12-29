#include "PUMA.h"
#include <exception>
#include "Rendering/MeshGenerator.h"
#include "kbmath.h"
#include "Rendering/Shader.h"
#include "Rendering/Renderer.h"
#include "Rendering/RenderCommand.h"

namespace kb
{
	PUMA::PUMA(PUMAState& initState)
		: m_CurrentState(initState)
	{
		m_BaseArmMesh = MeshGenerator::Cylinder(0.2f, 1.0f, 30);
		m_ArmModelMtx.resize(m_ArmsCount);
		Update(initState);
	}

	void PUMA::Update(PUMAState& s)
	{
		m_CurrentState = s;
		UpdateConfiguration(s);
		UpdateMesh(s);
	}

	void PUMA::Render(const kbm::Mat4& viewProjection)
	{
		auto shader = ShaderLib::Get("Ambient");
		for (int i = 0; i < m_ArmsCount; i++)
		{
			auto modelMtx = m_ArmModelMtx[i] * m_BaseArmModelMtx[i];
			shader->SetMat4("u_VP", viewProjection);
			shader->SetVec3("u_Color", m_ArmColors[i]);
			Renderer::Submit(shader, m_BaseArmMesh, GL_TRIANGLES, modelMtx);
		}
		shader = ShaderLib::Get("Gizmo");
		shader->SetMat4("u_VP", viewProjection);
		shader->SetMat4("u_Model", m_EffectorModelMtx);
		RenderCommand::SetLineThickness(10.0f);
		Renderer::SubmitProcedural(shader, 6, GL_LINES);
		RenderCommand::SetLineThickness(1.0f);
	}

	void PUMA::UpdateConfiguration(PUMAState& s)
	{
		m_ArmModelMtx[0] = kbm::RotationY(s.a[0]);
		m_ArmModelMtx[1] = m_ArmModelMtx[0]
			* kbm::TranslationMatrix(0.0f, s.l[0], 0.0f)
			* kbm::RotationZ(s.a[1]);
		m_ArmModelMtx[2] = m_ArmModelMtx[1]
			* kbm::TranslationMatrix(s.l[1], 0.0f, 0.0f)
			* kbm::RotationZ(s.a[2]);
		m_ArmModelMtx[3] = m_ArmModelMtx[2]
			* kbm::TranslationMatrix(0.0f, -s.l[2], 0.0f)
			* kbm::RotationY(s.a[3]);
		m_EffectorModelMtx = m_ArmModelMtx[3]
			* kbm::TranslationMatrix(s.l[3] + 0.01f, 0.0f, 0.0f)
			* kbm::RotationX(s.a[4])
			* kbm::ScaleMatrix(0.3f, 0.3f, 0.3f);
	}

	void PUMA::UpdateMesh(PUMAState& s)
	{
		m_BaseArmModelMtx = {
			kbm::ScaleMatrix(1.0f, s.l[0], 1.0f),	// 1. arm
			kbm::EulerZXZRotation(-90.0f, 0.0f, 0.0f)
			* kbm::ScaleMatrix(1.0f, s.l[1], 1.0f),	// 2. arm
			kbm::EulerZXZRotation(180.0f, 0.0f, 0.0f)
			* kbm::ScaleMatrix(1.0f, s.l[2], 1.0f),	// 3. arm
			kbm::EulerZXZRotation(-90.0f, 0.0f, 0.0f)
			* kbm::ScaleMatrix(1.0f, s.l[3], 1.0f)	// 4. arm
		};
	}
}