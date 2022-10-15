#pragma once
#include <Engine/Bindable/Bindable.h>
#include <span>

struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
namespace ver
{
	//class RenderTarget : public Bindable
	//{
	//public:
	//	RenderTarget() = default;
	//	winrt::Windows::Foundation::IAsyncAction
	//		InitializeAsync(uint32_t width, uint32_t height, uint32_t ntargets);
	//public:
	//	void Bind(Graphics& gfx) noexcept override;
	//private:
	//	winrt::com_array<ID3D11RenderTargetView> targets;
	//};

	class BackBuffer : public GraphicsResource
	{
		static constexpr std::array<float, 4> clear_color {0.0f, 0.0f, 0.0f, 0.0f};
	public:
		BackBuffer() = default;
		~BackBuffer();
		winrt::Windows::Foundation::IAsyncAction
			InitializeAsync(Graphics& gfx, ID3D11Texture2D* texture);
		void Clear(Graphics& gfx) noexcept { Clear(gfx, clear_color); }
		void Clear(Graphics& gfx, std::span<const float, 4> color) noexcept;
	private:
		uint32_t width = 0, height = 0;
		winrt::com_ptr<ID3D11RenderTargetView> target;
	};
}