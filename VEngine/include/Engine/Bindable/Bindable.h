#pragma once
#include <Engine/Bindable/GraphicsResource.h>

namespace ver
{
	class Bindable : public GraphicsResource
	{
	public:
		virtual ~Bindable() = default;
	public:
		virtual void Bind(Graphics& gfx)noexcept = 0;
	};
}