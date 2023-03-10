#pragma once

#include "Loader.h"

namespace IO
{
	class COBJLoader : public ILoader
	{
	private:
		int __loadDataFromFileV(const std::string& vFileName, std::shared_ptr<CMesh>& voMesh) override;
		bool __checkVertexRepeat(const std::vector<SVertex>& vVertices, const SVertex& vVertex);
	};
}