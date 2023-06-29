#pragma once
#include <Engine/Bindable/Bindable.h>
#include <winrt/base.h>
#include <d3d11_4.h>
#include <span>

struct ID3D11Buffer;

namespace ver
{
	class ConstantBuffer : public Bindable
	{
	public:
		ConstantBuffer() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, std::span<const std::byte> consts, uint32_t slot = 0u);
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t size, uint32_t slot = 0u);
	public:
		void Update(Graphics& gfx, std::span<const std::byte> consts);
	protected:
		winrt::com_ptr<ID3D11Buffer> pConstantBuffer;
		uint32_t slot;
	};

	template<typename C>
	class ConstantBufferT : public ConstantBuffer
	{
	public:
		ConstantBufferT() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, const C& consts, uint32_t slot = 0u)
		{
			co_await ConstantBuffer::InitializeAsync(gfx, std::span<const std::byte>(reinterpret_cast<const std::byte*>(&consts), sizeof(C)), slot);
		}
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t slot = 0u)
		{
			co_await ConstantBuffer::InitializeAsync(gfx, sizeof(C), slot);
		}
	public:
		void Update(Graphics& gfx, const C& consts)
		{
			ConstantBuffer::Update(gfx, std::span<const std::byte>(reinterpret_cast<const std::byte*>(&consts), sizeof(C)));
		}
	};

	template<typename C>
	class VertexConstantBuffer : public ConstantBufferT<C>
	{
	public:
		using ConstantBufferT<C>::ConstantBufferT;
	public:
		void Bind(Graphics& gfx)noexcept override
		{
			auto* x = ConstantBuffer::pConstantBuffer.get();
			ConstantBuffer::GetContext(gfx)->VSSetConstantBuffers(ConstantBuffer::slot, 1u, &x);
		}
	};

	template<typename C>
	class PixelConstantBuffer : public ConstantBufferT<C>
	{
	public:
		using ConstantBufferT<C>::ConstantBufferT;
		void Bind(Graphics& gfx)noexcept override
		{
			auto* x = ConstantBuffer::pConstantBuffer.get();
			ConstantBuffer::GetContext(gfx)->PSSetConstantBuffers(ConstantBuffer::slot, 1u, &x);
		}
	};

}
