#pragma once
#include <memory>
#include <Framework\DXGIInfoManager.h>
#include <Engine/Bindable/BackBuffer.h>

struct ID3D11Device;
struct IDXGISwapChain;
struct ID3D11DeviceContext;

namespace ver
{
	class BackBuffer;

	class Graphics
	{
		friend class GraphicsResource;
	public:
		Graphics(uint32_t width, uint32_t height);
		Graphics(const Graphics&) = delete;
		~Graphics();
		Graphics& operator=(const Graphics&) = delete;
		winrt::IAsyncAction InitializeAsync(HWND wnd);
	public:
		void BeginFrame(float r, float g, float b)noexcept;
		void EndFrame();

		DirectX::XMMATRIX GetCamera()const noexcept { return camera; }
		void SetCamera(DirectX::XMMATRIX Camera)noexcept { camera = Camera; }

		DirectX::XMMATRIX GetProjection() const noexcept { return projection; }
		void SetProjection(DirectX::FXMMATRIX proj) noexcept { projection = proj; }


		void DrawIndexed(UINT count)noexcept;
		uint32_t GetWidth() const noexcept { return width; }
		uint32_t GetHeight() const noexcept { return height; }
		BackBuffer& GetTarget() { return target; }

		winrt::IAsyncAction OnResizeAsync(uint32_t newwidth, uint32_t newheight);
	private:
		winrt::IAsyncAction CreateBackBufferAsync();
	private:
		winrt::com_ptr<ID3D11Device> pDevice;
		winrt::com_ptr<IDXGISwapChain> pSwap;
		winrt::com_ptr<ID3D11DeviceContext> pContext;
		BackBuffer target;
		uint32_t width;
		uint32_t height;

		DirectX::XMMATRIX camera;
		DirectX::XMMATRIX projection;

#ifndef NDEBUG
		DXGIInfoManager infoManager;
#endif
	};

}
