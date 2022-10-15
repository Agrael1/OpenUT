#include <Engine/Bindable/IndexBuffer.h>

winrt::IAsyncAction ver::IndexBuffer::InitializeAsync(Graphics& gfx, std::span<const uint32_t> indices)
{
	co_await winrt::resume_background();
	count = indices.size();

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = UINT(count * sizeof(uint32_t));
	ibd.StructureByteStride = sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	winrt::check_hresult(GetDevice(gfx)->CreateBuffer(&ibd, &isd, pIndexBuffer.put()));
}