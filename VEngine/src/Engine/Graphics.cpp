#include <Engine/Graphics.h>
#include <Engine/Bindable/RenderTarget.h>

using namespace ver;

namespace dx = DirectX;

// Graphics
Graphics::Graphics(uint32_t width, uint32_t height)
	: width(width),
	height(height)
{
	
}
ver::Graphics::~Graphics()
{
}

void Graphics::BeginFrame(float r, float g, float b) noexcept
{

}
void Graphics::EndFrame()
{
	winrt::check_hresult(pSwap->Present(1u, 0u));
}
void Graphics::DrawIndexed(UINT count) noexcept
{
	pContext->DrawIndexed(count, 0u, 0u);
}

winrt::IAsyncAction Graphics::OnResizeAsync(unsigned newwidth, unsigned newheight)
{
	pTarget.reset();
	winrt::check_hresult(pSwap->ResizeBuffers(0, newwidth, newheight, DXGI_FORMAT_UNKNOWN, 0));
	width = newwidth;
	height = newheight;

	co_await CreateBackBufferAsync();
}

winrt::IAsyncAction ver::Graphics::CreateBackBufferAsync()
{
	winrt::apartment_context ui_thread;

	winrt::com_ptr<ID3D11Texture2D> pBackBuffer;
	winrt::check_hresult(pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), pBackBuffer.put_void()));
	pTarget = std::make_unique<BackBuffer>();
	auto action = pTarget->InitializeAsync(*this, pBackBuffer.get());


	co_await ui_thread; //context requires UI thread

	// viewport always fullscreen (for now)
	D3D11_VIEWPORT vp{};
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);
	co_await action;
}

winrt::IAsyncAction ver::Graphics::InitiaizeAsync(HWND wnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = wnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// create device and front/back buffers, and swap chain and rendering context
	winrt::check_hresult(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		pSwap.put(),
		pDevice.put(),
		nullptr,
		pContext.put()
	));

	co_await CreateBackBufferAsync();
}
