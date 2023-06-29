#include <Engine/Model/Mesh.h>
#include <Engine/Model/Material.h>
#include <assimp/mesh.h>

winrt::IAsyncAction ver::Mesh::InitializeAsync(Graphics& gfx, const Material& mat, aiMesh& mesh, float scale)
{
	//_vbuffer = mat.MakeVertexBindable(gfx, mesh, scale);
	//_ibuffer = mat.MakeIndexBindable(gfx, mesh);

	//for (auto& t : mat.GetTechniques())
	//{
	//	AddTechnique(std::move(t));
	//}
	co_return;
}

winrt::IAsyncAction ver::Mesh::ExtractVertsAsync(Graphics& gfx, aiMesh& mesh, float scale)
{
	co_return;
}