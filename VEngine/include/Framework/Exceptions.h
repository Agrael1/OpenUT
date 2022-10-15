#pragma once
#include <string>
#include <source_location>

namespace ver
{
	class DXGIInfoManager;
	class gfx_exception
	{
		static constexpr std::string_view type = "Veritas Graphics Exception";
	public:
		gfx_exception(winrt::hresult hr, std::string msg, const std::source_location& loc = std::source_location::current());
	public:
		std::string_view what()const noexcept { return info; }
	private:
		std::string info;
	};



	[[noreturn]] void throw_gfx(winrt::hresult hr, const DXGIInfoManager& man, const std::source_location& loc = std::source_location::current());
	inline void check_gfx(winrt::hresult hr, const DXGIInfoManager& man, const std::source_location& loc = std::source_location::current())
	{
		if (hr < 0)throw_gfx(hr, man, loc);
	}
}