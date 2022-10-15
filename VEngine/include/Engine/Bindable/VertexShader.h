#pragma once
#include <Engine/Bindable/Bindable.h>
#include <pplawait.h>
#include <winrt/base.h>
#include <filesystem>

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;
struct ID3D11VertexShader;

namespace ver
{
	class VertexShader : public Bindable
	{
	public:
		VertexShader() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, std::filesystem::path path);
	public:
		void Bind(Graphics& gfx)noexcept override;
		ID3DBlob* GetBytecode() const noexcept;
		static concurrency::task<std::shared_ptr<VertexShader>>
			ResolveAsync(Graphics& gfx, std::filesystem::path path);
		static std::wstring GenerateUID(const std::filesystem::path& path);
		std::wstring_view GetUID() const noexcept;
	protected:
		std::filesystem::path path;
		winrt::com_ptr<ID3DBlob> pBytecodeBlob;
		winrt::com_ptr<ID3D11VertexShader> pVertexShader;
	};
}
