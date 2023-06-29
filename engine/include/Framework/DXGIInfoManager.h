#pragma once
#include <vector>
#include <string>
#include <DXGIDebug.h>

namespace ver
{
	class DXGIInfoManager
	{
	public:
		DXGIInfoManager();
	public:
		std::vector<std::string> GetMessages()const;
		std::string GetMessageDump()const;
	private:
		winrt::com_ptr<IDXGIInfoQueue> pDxgiInfoQueue;
		wil::unique_hmodule lib;
	};
}
