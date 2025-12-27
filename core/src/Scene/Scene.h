#pragma once
#include "Rendering/PerspectiveCamera.h"
#include "kbmath.h"

namespace kb
{
	class Scene
	{
	public:
		virtual ~Scene() = default;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender(const kbm::Mat4& viewProjection) = 0;
	};
}