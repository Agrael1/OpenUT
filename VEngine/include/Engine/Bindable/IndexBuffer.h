#pragma once
#include <Engine/Bindable/Bindable.h>
#include <span>

struct ID3D11Buffer;

namespace ver
{
	class IndexBuffer : public Bindable
	{
	public:
		IndexBuffer() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, std::span<const uint32_t> indices);
	public:
		void Bind(Graphics& gfx) noexcept override;
		uint32_t GetCount() const noexcept { return count; }
	protected:
		size_t count = 0;
		winrt::com_ptr<ID3D11Buffer> pIndexBuffer;
	};
}

