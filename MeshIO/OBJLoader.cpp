#include "pch.h"
#include "OBJLoader.h"

using namespace IO;
using SPos = Vector3f;
using SNormal = Vector3f;
using SUV = Vector2f;

_REGISTER_EXCLUSIVE_PRODUCT(COBJLoader, OBJ_LOADER)

//*****************************************************************
//FUNCTION:
int COBJLoader::__loadDataFromFileV(const std::string& vFileName, std::shared_ptr<CMesh>& voMesh)
{
	std::fstream FileStream;
	FileStream.open(vFileName, std::ios::in);
	std::string Line;

	std::vector<SFace> Faces;
	std::vector<SVertex> Vertices;
	std::vector<SPos> Poses;
	std::vector<SNormal> Normals;
	std::vector<SUV> UVs;

	std::uint32_t LineCount = -1;
	while (std::getline(FileStream, Line)) 
	{
		LineCount++;
		std::vector<std::string> SpaceSplit;
		boost::split(SpaceSplit, Line, boost::is_any_of(" "), boost::token_compress_on);

		if (Line[0] != 'v') continue; 
		if (Line[1] == 'n')
		{
			_HIVE_EARLY_RETURN(SpaceSplit.size() != 3, _FORMAT_STR1("Line: %1%, value size is nor correct", LineCount), -1);
			Normals.push_back(SNormal(std::atof(SpaceSplit[0].c_str()), std::atof(SpaceSplit[1].c_str()), std::atof(SpaceSplit[2].c_str())));
		}
		else if (Line[1] == 't')
		{
			_HIVE_EARLY_RETURN(SpaceSplit.size() != 2, _FORMAT_STR1("Line: %1%, value size is nor correct", LineCount), -1);
			UVs.push_back(SUV(std::atof(SpaceSplit[0].c_str()), std::atof(SpaceSplit[1].c_str())));
		}
		else
		{
			_HIVE_EARLY_RETURN(SpaceSplit.size() != 3, _FORMAT_STR1("Line: %1%, value size is nor correct", LineCount), -1);
			Poses.push_back(SPos(std::atof(SpaceSplit[0].c_str()), std::atof(SpaceSplit[1].c_str()), std::atof(SpaceSplit[2].c_str())));
		}
	}

	_HIVE_EARLY_RETURN(Poses.size() == 0, "OBJ File has no valid positions", -1);
	bool IsNormal = (Normals.size() > 0) ? true : false;
	bool IsUV = (UVs.size() > 0) ? true : false;

	FileStream.clear();
	FileStream.seekg(0, std::ios::beg);
	LineCount = -1;
	while (std::getline(FileStream, Line))
	{
		LineCount++;
		std::vector<std::string> SpaceSplit;
		boost::split(SpaceSplit, Line, boost::is_any_of(" "), boost::token_compress_on);

		if (Line[0] != 'f') continue;
		for (const auto& e : SpaceSplit)
		{
			std::vector<std::string> ObliqueSplit;
			boost::split(ObliqueSplit, e, boost::is_any_of("/"), boost::token_compress_on);
			std::vector<std::uint32_t> Indices;
			for (const auto& t : ObliqueSplit)
				Indices.push_back(std::atoi(t.c_str()));

			std::uint32_t PosIndex = std::atoi(ObliqueSplit[0].c_str()) - 1;
			std::uint32_t NormalIndex = (IsNormal) ? std::atoi(ObliqueSplit[1].c_str()) - 1 : -1;
			std::uint32_t UVIndex = (IsUV) ? ((IsNormal) ? std::atoi(ObliqueSplit[2].c_str()) - 1 : std::atoi(ObliqueSplit[1].c_str()) - 1) : -1;

			SVertex Vertex(Poses[PosIndex].x, Poses[PosIndex].y, Poses[PosIndex].z);
			Vertex.nx = (IsNormal) ? Normals[NormalIndex].x : 0;
			Vertex.ny = (IsNormal) ? Normals[NormalIndex].y : 0;
			Vertex.nz = (IsNormal) ? Normals[NormalIndex].z : 0;
			Vertex.u = (IsUV) ? UVs[UVIndex].x : 0;
			Vertex.v = (IsUV) ? UVs[UVIndex].y : 0;

			// if vertex repeat
			Vertices.emplace_back(Vertex);
		}
	}

	FileStream.close();
	return 0;
}