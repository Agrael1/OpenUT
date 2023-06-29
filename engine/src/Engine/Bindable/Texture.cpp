#include <Engine/Bindable/Texture.h>

winrt::IAsyncAction ver::Texture::InitializeAsync(Graphics& gfx, std::filesystem::path path, uint32_t slot)
{
	co_await winrt::resume_background();
	//Surface s;
	//if (!s.FromFile(path))
	//	co_return ResolveToDefault(gfx);

	//hasAlpha = s.UsesAlpha();

	//winrt::check_hresult(DirectX::CreateShaderResourceView(GetDevice(gfx),
	//	s->GetImages(), s->GetImageCount(),
	//	s->GetMetadata(), &pTextureView
	//));
	//s->Release();
}