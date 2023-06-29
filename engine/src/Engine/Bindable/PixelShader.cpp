#include <Engine/Bindable/PixelShader.h>
#include <Engine/Bindable/Codex.h>
#include <d3dcompiler.h>


winrt::IAsyncAction ver::PixelShader::InitializeAsync(Graphics& gfx, std::filesystem::path path)
{
	co_await winrt::resume_background();
	winrt::com_ptr<ID3DBlob> pBlob;
	winrt::check_hresult(D3DReadFileToBlob(path.native().c_str(), pBlob.put()));
	winrt::check_hresult(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, pPixelShader.put()));
	this->path = std::move(path);
}

void ver::PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.get(), nullptr, 0u);
}

concurrency::task<std::shared_ptr<ver::PixelShader>> ver::PixelShader::ResolveAsync(Graphics& gfx, std::filesystem::path path)
{
	co_return co_await Codex::ResolveAsync<ver::PixelShader>(gfx, path);
}

std::wstring ver::PixelShader::GenerateUID(const std::filesystem::path& path)
{
	return path.native().c_str();
}

std::wstring_view ver::PixelShader::GetUID() const noexcept
{
	return path.native().c_str();
}
