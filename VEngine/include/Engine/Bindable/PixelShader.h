#pragma once
#include <Engine/Bindable/Bindable.h>
#include <filesystem>
#include <pplawait.h>
#include <winrt/base.h>

struct ID3D11PixelShader;

namespace ver
{
	class PixelShader : public Bindable
	{
	public:
		PixelShader() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, std::filesystem::path path);
	public:
		void Bind(Graphics& gfx) noexcept override;
		static concurrency::task<std::shared_ptr<PixelShader>>
			ResolveAsync(Graphics& gfx, std::filesystem::path path);
		static std::wstring GenerateUID(const std::filesystem::path& path);
		std::wstring_view GetUID() const noexcept;
	protected:
		std::filesystem::path path;
		winrt::com_ptr<ID3D11PixelShader> pPixelShader;
	};
}
