#include <Engine/Bindable/ConstantBuffer.h>
#include <d3d11_4.h>


winrt::IAsyncAction ver::ConstantBuffer::InitializeAsync(Graphics& gfx, std::span<const std::byte> consts, uint32_t xslot)
{
	co_await winrt::resume_background();
	slot = xslot;
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = consts.size_bytes();
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &consts;
	winrt::check_hresult(GetDevice(gfx)->CreateBuffer(&cbd, &csd, pConstantBuffer.put()));
}

winrt::IAsyncAction ver::ConstantBuffer::InitializeAsync(Graphics& gfx, uint32_t size, uint32_t slot)
{
	co_await winrt::resume_background();
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = size;
	cbd.StructureByteStride = 0u;

	winrt::check_hresult(GetDevice(gfx)->CreateBuffer(&cbd, nullptr, pConstantBuffer.put()));
}

void ver::ConstantBuffer::Update(Graphics& gfx, std::span<const std::byte> consts)
{
	D3D11_MAPPED_SUBRESOURCE msr = {};
	winrt::check_hresult(GetContext(gfx)->Map(
		pConstantBuffer.get(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u,
		&msr
	));
	memcpy(msr.pData, consts.data(), consts.size());
	GetContext(gfx)->Unmap(pConstantBuffer.get(), 0u);
}
