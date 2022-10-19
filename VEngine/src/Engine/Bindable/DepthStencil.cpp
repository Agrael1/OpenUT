#include <Engine/Bindable/DepthStencil.h>
#include <Engine/Graphics.h>

using namespace ver;

winrt::IAsyncAction DepthStencil::InitializeAsync(Graphics& gfx, uint32_t width, uint32_t height, bool canBindShaderInput)
{
	co_await winrt::resume_background();
	// create depth stensil texture
	winrt::com_ptr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // this will need to be fixed
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | (canBindShaderInput ? D3D11_BIND_SHADER_RESOURCE : 0);
	winrt::check_hresult(GetDevice(gfx)->CreateTexture2D(&descDepth, nullptr, pDepthStencil.put()));

	// create target view of depth stensil texture
	winrt::check_hresult(GetDevice(gfx)->CreateDepthStencilView(
		pDepthStencil.get(), nullptr, pDepthStencilView.put() // nullptr will need to be replaced
	));

	if (canBindShaderInput)
	{
		winrt::com_ptr<ID3D11Resource> pRes;
		pDepthStencilView->GetResource(pRes.put());

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // this will need to be fixed
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		winrt::check_hresult(GetDevice(gfx)->CreateShaderResourceView(
			pRes.get(), &srvDesc, pShaderResourceView.put()
		));
	}
}

void ver::DepthStencil::Clear(Graphics& gfx) noexcept
{
	GetContext(gfx)->ClearDepthStencilView(pDepthStencilView.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}