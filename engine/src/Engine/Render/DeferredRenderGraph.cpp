#include <Engine/Render/DeferredRenderGraph.h>
#include <Engine/Graphics.h>

using namespace ver::rg;

winrt::IAsyncAction DeferredRenderGraph::InitializeAsync(Graphics& gfx)
{
	co_await winrt::when_all(gbuffer.InitializeAsync(gfx, gfx.GetWidth(), gfx.GetHeight())
		, depth.InitializeAsync(gfx, gfx.GetWidth(), gfx.GetHeight(), true));
	master = gfx.GetTarget();
}