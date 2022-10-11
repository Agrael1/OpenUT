#include <Framework/DXGIInfoManager.h>

using namespace ver;

DXGIInfoManager::DXGIInfoManager()
{
	// define signature of the function
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	lib.reset(LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32));
	winrt::check_bool(lib.is_valid());
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(lib.get(), "DXGIGetDebugInterface"))
		);
	winrt::check_pointer(DxgiGetDebugInterface);
	winrt::throw_hresult(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), pDxgiInfoQueue.put_void()));
}

std::vector<std::string> DXGIInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (UINT64 i = 0; i < end; i++)
	{
		size_t messageLength = 0;
		// get the size of message[i]
		pDxgiInfoQueue->GetMessageA(DXGI_DEBUG_ALL, i, nullptr, &messageLength);
		// allocate memory for message
		auto bytes = std::make_unique<std::byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get message and bush it into vector
		pDxgiInfoQueue->GetMessageA(DXGI_DEBUG_ALL, i, pMessage, &messageLength);
		messages.emplace_back(pMessage->pDescription);
	}
	pDxgiInfoQueue->ClearStoredMessages(DXGI_DEBUG_ALL);
	return messages;
}
