#pragma once
#include <Engine/Bindable/Bindable.h>
#include <winrt/base.h>

struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;

namespace ver
{
	class DepthStencil : public GraphicsResource
	{
	public:
		DepthStencil() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t width, uint32_t height, bool canBindShaderInput);
	public:
		void Clear(Graphics& gfx) noexcept;
		ID3D11DepthStencilView* GetRaw()const noexcept
		{
			return pDepthStencilView.get();
		}
	protected:
		uint32_t slot = 0u;
		winrt::com_ptr<ID3D11DepthStencilView> pDepthStencilView;
		winrt::com_ptr<ID3D11ShaderResourceView> pShaderResourceView;
	};
}

