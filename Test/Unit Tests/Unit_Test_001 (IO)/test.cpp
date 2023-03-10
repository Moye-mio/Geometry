#include "pch.h"

const std::string CubePath = TESTMODEL_DIR + std::string("/Cube.obj");

class TestIO : public testing::Test
{
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

TEST(TestIO, NT_Cube)
{
	const std::string Path = CubePath;
	auto* pMeshLoader = hiveDesignPattern::hiveGetOrCreateProduct<IO::ILoader>(hiveUtility::hiveGetFileSuffix(Path));
	ASSERT_TRUE(pMeshLoader);
	std::shared_ptr<CMesh> pData = pMeshLoader->loadDataFromFile(Path);
	ASSERT_FALSE(pData);
}