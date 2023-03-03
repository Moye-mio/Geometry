#pragma once

#include "Types.h"

using DataType = float;
using IndexType = std::uint32_t;

struct SVertex
{
	DataType x = 0;
	DataType y = 0;
	DataType z = 0;
	DataType nx = 0;
	DataType ny = 0;
	DataType nz = 0;
	DataType u = -1;
	DataType v = -1;

	Vector3f xyz() const { return { x, y, z }; }
	Vector3f normal() const { return { nx, ny, nz }; }
	Vector2f uv() const { return { u, v }; }

	DataType operator[](IndexType i) const
	{
		if (i >= 0 && i < sizeof(SVertex) / sizeof(DataType))
			return *(reinterpret_cast<const DataType*>(this) + i);
		else
			return -1;
	}

	bool operator < (const SVertex& Vertex) const
	{
		if (this->xyz().norm() < Vertex.xyz().norm())
			return true;
		else
			return false;
	}

	bool operator == (const SVertex& Vertex) const
	{
		for (int i = 0; i < sizeof(SVertex) / sizeof(DataType); i++)
			if ((*this)[i] != Vertex[i])
				return false;
		return true;
	}

	SVertex lerp(const SVertex& vOther, float vMix = 0.5f) const
	{
		using std::lerp;

		SVertex NewVertex;
		NewVertex.x = lerp(x, vOther.x, vMix);
		NewVertex.y = lerp(y, vOther.y, vMix);
		NewVertex.z = lerp(z, vOther.z, vMix);
		NewVertex.nx = lerp(nx, vOther.nx, vMix);
		NewVertex.ny = lerp(ny, vOther.ny, vMix);
		NewVertex.nz = lerp(nz, vOther.nz, vMix);
		NewVertex.u = lerp(u, vOther.u, vMix);
		NewVertex.v = lerp(v, vOther.v, vMix);
		return NewVertex;
	}
};



class CMesh
{
public:



private:
};
