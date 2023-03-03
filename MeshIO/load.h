#pragma once

namespace IO
{
	class ILoader : public hiveDesignPattern::IProduct
	{
	public:
		ILoader() = default;
		~ILoader() override = default;

		PC_t::Ptr loadDataFromFile(const std::string& vFileName);

	private:
		virtual int __loadDataFromFileV(const std::string& vFileName, PC_t& voPointCloud) = 0;
	};
}