#pragma once

#include "Mesh.h"

namespace IO
{
	class ILoader : public hiveDesignPattern::IProduct
	{
	public:
		ILoader() = default;
		~ILoader() override = default;

		std::shared_ptr<CMesh> loadDataFromFile(const std::string& vFileName);

	private:
		virtual int __loadDataFromFileV(const std::string& vFileName, std::shared_ptr<CMesh>& voMesh) = 0;
	};
}