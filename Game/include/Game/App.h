#pragma once

namespace UT
{
	class App
	{
		static constexpr uint32_t def_width = 1920;
		static constexpr uint32_t def_height = 1080;
	public:
		App();
	public:
		int Go();
	private:
		void DoFrame(float dt);
		void ProcessInput(float dt);
	private:
	};
}
