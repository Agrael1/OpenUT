#pragma once
#include <Engine/Bindable/Bindable.h>
#include <winrt/base.h>
#include <span>

struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;

namespace ver
{
	class DepthStencil;

	class RenderTarget
	{
	public:
		RenderTarget() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t width, uint32_t height);
	public:
		void Bind(Graphics& gfx) noexcept;
		void Clear(Graphics& gfx) noexcept;
		void Clear(Graphics& gfx, const std::array<float, 4>& color) noexcept;
		uint32_t GetWidth() const noexcept;
		uint32_t GetHeight() const noexcept;
	private:
		void BindAsBuffer(Graphics& gfx, ID3D11DepthStencilView* pDepthStencilView) noexcept;
	protected:
		uint32_t width = 0u;
		uint32_t height = 0u;
		uint32_t slot = 0u;
		winrt::com_ptr<ID3D11RenderTargetView> pTargetView;
		winrt::com_ptr<ID3D11ShaderResourceView> pShaderResourceView;
	};


	class RenderTargetSpan : public GraphicsResource
	{
	public:
		RenderTargetSpan(std::span<winrt::com_ptr<ID3D11RenderTargetView>> targets,
			std::span<winrt::com_ptr<ID3D11ShaderResourceView>> resource_views) :targets(targets), resource_views(resource_views) {}

		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t width, uint32_t height);
		void Bind(Graphics& gfx, DepthStencil& depthStencil) noexcept;
	private:
		std::span<winrt::com_ptr<ID3D11RenderTargetView>> targets;
		std::span<winrt::com_ptr<ID3D11ShaderResourceView>> resource_views;
	};

	

	template<size_t size = 1>
	class RenderTargetArray
	{
	public:
		RenderTargetArray() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t xwidth, uint32_t xheight)
		{
			width = xwidth; height = xheight;
			co_await operator RenderTargetSpan().InitializeAsync(gfx, width, height);
		}
		operator RenderTargetSpan()
		{
			return RenderTargetSpan{ targets,resource_views };
		}
	public:
		uint32_t GetWidth() const noexcept { return width; }
		uint32_t GetHeight() const noexcept { return height; }
	private:
		void BindAsBuffer(Graphics& gfx, ID3D11DepthStencilView* pDepthStencilView) noexcept;
	protected:
		uint32_t width = 0u;
		uint32_t height = 0u;
		std::array<winrt::com_ptr<ID3D11RenderTargetView>, size> targets;
		std::array<winrt::com_ptr<ID3D11ShaderResourceView>, size> resource_views;
	};
}
