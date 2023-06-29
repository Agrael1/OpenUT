#pragma once
#include <Engine/Render/RenderPass.h>
#include <Engine/Render/LightingPass.h>
#include <Engine/Bindable/DepthStencil.h>

namespace ver { class Graphics; };

namespace ver::rg
{
	class Drawable;
	class DeferredRenderGraph
	{
	public:
		DeferredRenderGraph() {}
		winrt::IAsyncAction InitializeAsync(Graphics& gfx);
	public:
		void Execute(Graphics& gfx)noexcept
		{
			auto x = RenderTargetSpan(gbuffer);

			x.Bind(gfx, depth);
			render.Execute(gfx);
			
			lighting.Execute(gfx, gbuffer, master, depth);
		}
		void Submit(Drawable&);
	private:
		RenderTargetArray<3> gbuffer;
		DepthStencil depth;
		BackBuffer master;

		RenderPass render;
		LightingPass lighting;
	};
}