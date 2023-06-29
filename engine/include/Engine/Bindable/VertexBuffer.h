#pragma once
#include <Engine/Bindable/Bindable.h>
#include <Engine/Dynamic/VertexLayout.h>
#include <winrt/base.h>
#include <memory>

struct ID3D11Buffer;

namespace ver::dv
{
	class VertexBuffer;
}

namespace ver
{
	class VertexBuffer : public Bindable
	{
	public:
		VertexBuffer() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, const dv::VertexBuffer& vbuf);
	public:
		dv::LayoutSpan GetLayout() const noexcept { return dv::LayoutSpan(layout); }
		void Bind(Graphics& gfx) noexcept override;
	protected:
		std::string tag;
		uint32_t stride;
		winrt::com_ptr<ID3D11Buffer> pVertexBuffer;
		dv::VertexLayout layout;
	};
}
