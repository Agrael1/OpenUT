#pragma once
#include <Engine/Bindable/VertexBuffer.h>
#include <Engine/Bindable/IndexBuffer.h>
#include <d3d11_4.h> 

namespace ver
{
	class Drawable
	{
	public:
		Drawable() = default;
	public:
		//winrt::IAsyncAction InitializeAsync();
		virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	protected:
		D3D11_PRIMITIVE_TOPOLOGY _topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		VertexBuffer _vbuffer;
		IndexBuffer _ibuffer;
	};
}