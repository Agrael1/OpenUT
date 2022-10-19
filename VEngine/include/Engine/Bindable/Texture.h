#pragma once
#include <Engine/Bindable/Bindable.h>
#include <winrt/base.h>
#include <pplawait.h>
#include <filesystem>

namespace ver
{
	class Texture : public Bindable
	{
	public:
		Texture() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, std::filesystem::path path, uint32_t slot = 0);
	public:
		void Bind(Graphics& gfx) noexcept override;
		static std::shared_ptr<Texture> Resolve(Graphics& gfx, std::string_view path, uint32_t slot = 0);
		static concurrency::task<std::shared_ptr<Texture>> ResolveAsync(Graphics& gfx, std::string path, uint32_t slot = 0);
		static std::string GenerateUID(std::string_view path, uint32_t slot = 0);
		std::string GetUID() const noexcept;
		bool UsesAlpha() const noexcept;
	private:
		static uint32_t CalculateNumberOfMipLevels(uint32_t width, uint32_t height) noexcept;
		void ResolveToDefault(Graphics& gfx);
	private:
		unsigned int slot;
	protected:
		std::filesystem::path path;
		winrt::com_ptr<ID3D11ShaderResourceView> pTextureView;
		bool hasAlpha = false;
	};
}
