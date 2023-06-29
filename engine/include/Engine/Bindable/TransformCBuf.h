#pragma once
#include <Engine/Bindable/Bindable.h>
#include <DirectXMath.h>


namespace ver
{
	class Drawable;
	class Graphics;
	template<class T>
	class VertexConstantBuffer;

	class TransformCbuf : public Bindable
	{
	protected:
		struct Transforms
		{
			DirectX::XMMATRIX model;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX proj;
		};
	public:
		TransformCbuf() = default;
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, uint32_t slot = 0u);
	public:
		void Bind(Graphics& gfx) noexcept override;
		void InitializeParentReference(const Drawable& parent) noexcept { pParent = &parent; }
		//std::unique_ptr<CloningBindable> Clone() const noexcept override;
	protected:
		void UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept;
		Transforms GetTransforms(Graphics& gfx) noexcept;
	private:
		static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
		const Drawable* pParent = nullptr;
	};
}
