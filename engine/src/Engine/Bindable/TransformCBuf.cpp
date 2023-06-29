#include <Engine/Bindable/TransformCBuf.h>
#include <Engine/Bindable/ConstantBuffer.h>
#include <Engine/Render/Drawable.h>
#include <Engine/Graphics.h>

std::unique_ptr<ver::VertexConstantBuffer<ver::TransformCbuf::Transforms>> ver::TransformCbuf::pVcbuf = nullptr;

winrt::IAsyncAction ver::TransformCbuf::InitializeAsync(Graphics& gfx, uint32_t slot)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>();
		co_await pVcbuf->InitializeAsync(gfx, slot);
	}
}

void ver::TransformCbuf::Bind(Graphics& gfx) noexcept
{
	UpdateBindImpl(gfx, GetTransforms(gfx));
}

void ver::TransformCbuf::UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept
{
	assert(pParent != nullptr);
	pVcbuf->Update(gfx, tf);
	pVcbuf->Bind(gfx);
}

ver::TransformCbuf::Transforms ver::TransformCbuf::GetTransforms(Graphics& gfx) noexcept
{
	assert(pParent != nullptr);
	return {
		DirectX::XMMatrixTranspose(pParent->GetTransformXM()),
		DirectX::XMMatrixTranspose(gfx.GetCamera()),
		DirectX::XMMatrixTranspose(gfx.GetProjection())
	};
}
