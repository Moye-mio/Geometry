#include "pch.h"
#include "Loader.h"

using namespace IO;

std::shared_ptr<CMesh> ILoader::loadDataFromFile(const std::string& vFileName)
{
	_ASSERTE(!vFileName.empty());

	std::string FileName = hiveUtility::hiveLocateFile(vFileName);
	_HIVE_EARLY_RETURN(FileName.empty(), _FORMAT_STR1("Fail to load file [%1%] because it does not exist.", vFileName), nullptr);

	std::shared_ptr<CMesh> pMesh;

	try
	{
		int r = __loadDataFromFileV(vFileName, pMesh);
		if (r == 0)
		{
			hiveEventLogger::hiveOutputEvent(_FORMAT_STR1("Succeed to load point cloud file [%1%].", vFileName));
			return pMesh;
		}
		else
		{
			pMesh.reset();
			_HIVE_OUTPUT_WARNING(_FORMAT_STR2("Fail to load file [%1%] due to error [%2%].", vFileName, r));
			return nullptr;
		}
	}
	catch (...)
	{
		pMesh.reset();
		_HIVE_OUTPUT_WARNING(_FORMAT_STR1("Fail to load file [%1%] due to unexpeced error.", vFileName));
		return nullptr;
	}
}
