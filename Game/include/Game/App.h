#pragma once
#include <Game/Window.h>
#include <Engine/Graphics.h>
#include <Engine/Render/DeferredRenderGraph.h>


namespace UT
{
	class App
	{
		static constexpr uint32_t def_width = 1920;
		static constexpr uint32_t def_height = 1080;
	public:
		App();
	public:
		winrt::IAsyncAction InitializeAsync();
		int Go();
	private:
		void DoFrame(float dt);
		void ProcessInput(float dt);
	private:
		Window wnd;
		ver::Graphics gfx;
		ver::rg::DeferredRenderGraph graph;
	};
}
