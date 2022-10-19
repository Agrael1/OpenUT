#pragma once
#include <Engine/Bindable/RenderTarget.h>
#include <Engine/Bindable/BackBuffer.h>

namespace ver
{
	class Graphics;
	class LightingPass
	{
	public:
		LightingPass() {}
	public:
		void Execute(Graphics& gfx, RenderTargetArray<3>& rta, BackBuffer& buffer, DepthStencil& depth)noexcept
		{

		}
	private:
	};
}