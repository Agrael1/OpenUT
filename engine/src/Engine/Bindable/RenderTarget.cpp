#include <Engine/Bindable/RenderTarget.h>
#include <Engine/Bindable/DepthStencil.h>
#include <ranges>

using namespace ver;

winrt::com_ptr<ID3D11RenderTargetView> GetRTV(ID3D11Device* dev, uint32_t width, uint32_t height)
{
	winrt::com_ptr<ID3D11RenderTargetView> pTargetView;
	winrt::com_ptr<ID3D11Texture2D> pTexture;

	// create texture resource
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // never do we not want to bind offscreen RTs as inputs
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	winrt::check_hresult(dev->CreateTexture2D(
		&textureDesc, nullptr, pTexture.put()
	));

	// create the target view on the texture
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D = D3D11_TEX2D_RTV{ 0 };
	winrt::check_hresult(dev->CreateRenderTargetView(
		pTexture.get(), &rtvDesc, pTargetView.put()
	));
	return pTargetView;
}

winrt::com_ptr<ID3D11ShaderResourceView> GetSRV(ID3D11Device* dev, ID3D11RenderTargetView* rtv)
{
	winrt::com_ptr<ID3D11ShaderResourceView> pShaderResourceView;
	winrt::com_ptr<ID3D11Resource> pRes;
	rtv->GetResource(pRes.put());

	// create the resource view on the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	winrt::check_hresult(dev->CreateShaderResourceView(
		pRes.get(), &srvDesc, pShaderResourceView.put()
	));
	return pShaderResourceView;
}

winrt::IAsyncAction ver::RenderTargetSpan::InitializeAsync(Graphics& gfx, uint32_t width, uint32_t height)
{
	co_await winrt::resume_background();
	for (auto& i : targets)
	{
		i = GetRTV(GetDevice(gfx), width, height);
	}
	for (size_t i = 0; i < resource_views.size(); i++)
	{
		resource_views[i] = GetSRV(GetDevice(gfx), targets[i].get());
	}
}

void ver::RenderTargetSpan::Bind(Graphics& gfx, DepthStencil& depthStencil)noexcept
{
	GetContext(gfx)->OMSetRenderTargets(targets.size(), reinterpret_cast<ID3D11RenderTargetView*const* >(targets.data()), depthStencil.GetRaw());
}