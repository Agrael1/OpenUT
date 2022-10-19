#pragma once
#include <Engine/Render/Drawable.h>

class FrameCommander;
struct aiMesh;

namespace ver
{
	class Material;
	class Mesh : public Drawable
	{
	public:
		Mesh() = default;
	public:
		winrt::IAsyncAction InitializeAsync(Graphics& gfx, const Material& mat, aiMesh& mesh, float scale = 1.0f);
		//winrt::IAsyncAction InitializeAsync(Graphics& gfx);
		DirectX::XMMATRIX GetTransformXM() const noexcept override;
		void Submit(DirectX::FXMMATRIX accumulatedTranform) const noexcept;
	private:
		winrt::IAsyncAction ExtractVertsAsync(Graphics& gfx, aiMesh& mesh, float scale = 1.0f);
	private:
		mutable DirectX::XMFLOAT4X4 transform;
	};
}
