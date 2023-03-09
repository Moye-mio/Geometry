#include "pch.h"

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

TEST(TestIO, DT_InvalidInput)
{
	std::string s = "sss /ddd,ggg";
	std::vector<std::string> vStr;
	boost::split(vStr, s, boost::is_any_of(" "), boost::token_compress_on);
	for (std::vector<std::string>::iterator it = vStr.begin(); it != vStr.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	
}