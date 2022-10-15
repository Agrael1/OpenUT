#include <Engine/Bindable/VertexShader.h>
#include <d3dcompiler.h>
#include <Engine/Bindable/Codex.h>

using namespace ver;

winrt::IAsyncAction ver::VertexShader::InitializeAsync(Graphics& gfx, std::filesystem::path path)
{
	co_await winrt::resume_background();
	if (!std::filesystem::exists(path))
		co_return;

	winrt::check_hresult(D3DReadFileToBlob(path.native().c_str(), pBytecodeBlob.put()));
	winrt::check_hresult(GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		pVertexShader.put()
	));
	this->path = std::move(path);
}

void VertexShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.get();
}

concurrency::task<std::shared_ptr<VertexShader>> VertexShader::ResolveAsync(Graphics& gfx, std::filesystem::path path)
{
	co_return co_await Codex::ResolveAsync<VertexShader>(gfx, path);
}

std::wstring ver::VertexShader::GenerateUID(const std::filesystem::path & path)
{
	return path.native();
}
std::wstring_view VertexShader::GetUID() const noexcept
{
	return path.native().c_str();
}