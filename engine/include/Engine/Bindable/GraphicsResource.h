#pragma once

struct ID3D11DeviceContext;
struct ID3D11Device;
namespace ver
{
	class DXGIInfoManager;
	class Graphics;

	class GraphicsResource
	{
	protected:
		static ID3D11DeviceContext* GetContext(const Graphics& gfx) noexcept;
		static ID3D11Device* GetDevice(Graphics& gfx) noexcept;
		static DXGIInfoManager& GetInfoManager(Graphics& gfx);
	};
}