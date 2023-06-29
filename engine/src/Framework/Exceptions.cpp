#include <Framework/Exceptions.h>
#include <format>
#include <DxErr.h>
#include <Framework/DXGIInfoManager.h>

std::string ErrorHeader(const std::source_location& loc)
{
	return std::format("[File]: %s\n[Line]: %d\n[Function]: %s\n", loc.file_name(), loc.line(), loc.function_name());
}

std::string GetErrorString(winrt::hresult hr) noexcept
{
	return DXGetErrorString(hr);
}
std::string GetErrorDescription(winrt::hresult hr) noexcept
{
	return DXGetErrorDescription(hr);
}

ver::gfx_exception::gfx_exception(winrt::hresult hr, std::string msg, const std::source_location& loc)
	:info(/*std::format(
		"{}\n{}\n"
		"[Error Code]: {:#08x} ({})\n"
		"[Error String]: {}\n"
		"[Description]: {}\n"
		"[Message]: {}\n",
		type, hr, hr, GetErrorString(hr), GetErrorDescription(hr), msg
	)*/)
{
	
}

[[noreturn]]void ver::throw_gfx(winrt::hresult hr, const DXGIInfoManager& man, const std::source_location& loc)
{
	throw ver::gfx_exception(hr, man.GetMessageDump(), loc);
}
