#pragma once

#include "Types.h"
#include "Vertex.h"
#include "Face.h"

class CMesh
{
public:
	CMesh() = default;
	CMesh(const CMesh& m)
		: m_Vertices(m.m_Vertices)
		, m_Faces(m.m_Faces)
	{

	}
	CMesh(CMesh&& m)
		: m_Vertices(m.m_Vertices)
		, m_Faces(m.m_Faces)
	{
		m.m_Vertices.clear();
		m.m_Vertices.shrink_to_fit();
		m.m_Faces.clear();
		m.m_Faces.shrink_to_fit();
	}
	CMesh(const std::vector<SVertex>& vVertices, const std::vector<SFace>& vFaces)
		: m_Vertices(vVertices)
		, m_Faces(vFaces)
	{}
	~CMesh() = default;

	// members
	std::vector<SVertex>	m_Vertices;
	std::vector<SFace>		m_Faces;

private:
};
