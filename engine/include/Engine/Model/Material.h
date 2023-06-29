#pragma once
#include <filesystem>

struct aiMaterial;
struct aiMesh;


namespace ver
{
	class VertexBuffer;
	class IndexBuffer;
	class Graphics;
	class Material
	{
	public:
		Material() = default;
		//Material(Graphics& gfx, const aiMaterial& material, std::filesystem::path path) noexcept;
		winrt::IAsyncAction	InitializeAsync(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path);
	//public:
	//	DV::VertexBuffer ExtractVertices(const aiMesh& mesh) const noexcept;
	//	std::vector<unsigned short> ExtractIndices(const aiMesh& mesh) const noexcept;
	//	std::shared_ptr<VertexBuffer> MakeVertexBindable(Graphics& gfx, const aiMesh& mesh, float scale = 1.0f) const noxnd;
	//	std::shared_ptr<IndexBuffer> MakeIndexBindable(Graphics& gfx, const aiMesh& mesh) const noxnd;
	//	std::vector<Technique> GetTechniques() const noexcept;
	//private:
	//	std::string MakeMeshTag(const aiMesh& mesh) const noexcept;
	//private:
	//	DV::VertexLayout vtxLayout;
	//	//std::vector<Technique> techniques;
	//	std::string modelPath;
	//	std::string name;
	};
}
