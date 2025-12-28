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
	{
		m_Arms.resize(m_ArmsCount);
		for (int i = 0; i < m_ArmsCount; i++)
		{
			m_Arms[i] = {
				initState.l[i],
				initState.p[i],
				m_RotationAxes[i],
				initState.a[i]
			};
		}
		m_Effector = { initState.p[4], initState.a[4] };

		// Mesh
		m_BaseArmMesh = MeshGenerator::Cylinder(0.2f, 1.0f, 30);
		
		// Model matrices
		m_BaseArmModelMtx = {
			kbm::ScaleMatrix(1.0f, initState.l[0], 1.0f),	// 1. arm

			kbm::EulerZXZRotation(-90.0f, 0.0f, 0.0f)
			* kbm::ScaleMatrix(1.0f, initState.l[1], 1.0f),	// 2. arm

			kbm::EulerZXZRotation(180.0f, 0.0f, 0.0f)
			* kbm::ScaleMatrix(1.0f, initState.l[2], 1.0f),	// 3. arm

			kbm::EulerZXZRotation(-90.0f, 0.0f, 0.0f)
			* kbm::ScaleMatrix(1.0f, initState.l[3], 1.0f)	// 4. arm
		};

		m_ArmModelMtx.resize(m_ArmsCount);
		for (int i = 0; i < m_ArmsCount; i++)
			m_ArmModelMtx[i] = kbm::Identity();
		UpdateModelMatrices();
	}

	void PUMA::Update(PUMAState& newState)
	{
		for (int i = 0; i < m_ArmsCount; i++)
		{
			auto& arm = m_Arms[i];
			arm.Angle = newState.a[i];
			arm.Length = newState.l[i];
			arm.Origin = newState.p[i];
		}
		m_Effector = { newState.p[4], newState.a[4] };
		UpdateModelMatrices();
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

	void PUMA::UpdateModelMatrices()
	{
		m_ArmModelMtx[0] = kbm::RotationY(m_Arms[0].Angle);
		m_ArmModelMtx[1] = m_ArmModelMtx[0] 
			* kbm::TranslationMatrix(0.0f, m_Arms[0].Length, 0.0f) 
			* kbm::RotationZ(m_Arms[1].Angle);
		m_ArmModelMtx[2] = m_ArmModelMtx[1] 
			* kbm::TranslationMatrix(m_Arms[1].Length, 0.0f, 0.0f) 
			* kbm::RotationZ(m_Arms[2].Angle);
		m_ArmModelMtx[3] = m_ArmModelMtx[2]
			* kbm::TranslationMatrix(0.0f, -m_Arms[2].Length, 0.0f)
			* kbm::RotationY(m_Arms[3].Angle);
		m_EffectorModelMtx = m_ArmModelMtx[3]
			* kbm::TranslationMatrix(m_Arms[3].Length + 0.01f, 0.0f, 0.0f)
			* kbm::RotationX(m_Effector.a)
			* kbm::ScaleMatrix(0.3f, 0.3f, 0.3f);
	}

}