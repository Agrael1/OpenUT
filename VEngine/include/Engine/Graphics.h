#pragma once
#include <d3d11.h>
#include <memory>
#include <Framework\DXGIInfoManager.h>

//class RenderTarget;

namespace ver
{
	class Graphics
	{
		friend class GraphicsResource;
	public:
		Graphics(HWND hWnd, uint32_t width, uint32_t height);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		~Graphics();
	public:
		void EnableImgui()noexcept;
		void DisableImgui()noexcept;
		bool IsImguiEnabled()const noexcept;
		void BeginFrame(float r, float g, float b)noexcept;
		void EndFrame();

		DirectX::XMMATRIX GetCamera()const noexcept;
		void SetCamera(DirectX::XMMATRIX Camera)noexcept;
		void DrawIndexed(UINT count)noexcept;
		DirectX::XMMATRIX GetProjection() const noexcept;
		void SetProjection(DirectX::FXMMATRIX proj) noexcept;
		uint32_t GetWidth() const noexcept;
		uint32_t GetHeight() const noexcept;
		//std::shared_ptr<RenderTarget> GetTarget();
		void OnResize(uint32_t newwidth, uint32_t newheight);
	private:
		winrt::com_ptr<ID3D11Device> pDevice;
		winrt::com_ptr<IDXGISwapChain> pSwap;
		winrt::com_ptr<ID3D11DeviceContext> pContext;
		//std::shared_ptr<RenderTarget> pTarget;
		uint32_t width;
		uint32_t height;
#ifndef NDEBUG
		DXGIInfoManager infoManager;
#endif
	};

}
