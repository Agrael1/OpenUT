#include <Engine/Bindable/RenderTarget.h>

//winrt::Windows::Foundation::IAsyncAction 
//ver::RenderTarget::InitializeAsync(uint32_t width, uint32_t height, uint32_t ntargets)
//{
//	
//}


ver::BackBuffer::~BackBuffer()
{
}

winrt::Windows::Foundation::IAsyncAction
ver::BackBuffer::InitializeAsync(Graphics& gfx, ID3D11Texture2D* texture)
{
	co_await winrt::resume_background();

	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);
	width = textureDesc.Width;
	height = textureDesc.Height;

	// create the target view on the texture
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D = D3D11_TEX2D_RTV{ 0 };
	winrt::check_hresult(GetDevice(gfx)->CreateRenderTargetView(
		texture, &rtvDesc, target.put()
	));
}

void ver::BackBuffer::Clear(Graphics& gfx, std::span<const float, 4> color) noexcept
{
	GetContext(gfx)->ClearRenderTargetView(target.get(), color.data());
}