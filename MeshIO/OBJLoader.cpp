#include "pch.h"
#include "OBJLoader.h"

using namespace IO;

_REGISTER_EXCLUSIVE_PRODUCT(COBJLoader, OBJ_LOADER)

//*****************************************************************
//FUNCTION:
int COBJLoader::__loadDataFromFileV(const std::string& vFileName, std::shared_ptr<CMesh>& voMesh)
{
	std::fstream Stream;
	Stream.open(vFileName, std::ios::in);
	std::string Line;

	std::vector<SFace> Faces;
	std::vector<SVertex> Vertices;
	while (std::getline(Stream, Line)) 
	{
		if (Line[0] == 'v') 
		{
			if (sline[1] == 'n') {//vn
				vnNum++;
			}
			else if (sline[1] == 't') {//vt
				vtNum++;
			}
			else {//v
				vNum++;
			}
		}
		if (sline[0] == 'f') {
			istringstream ins(sline);
			s4.clear();
			ins >> s0 >> s1 >> s2 >> s3 >> s4;
			if (!s4.empty()) {
				fNum++;
				iNum++;
			}
			s4.clear();
			fNum++;
			iNum += 3;
		}
	}
	infile1.close();

}