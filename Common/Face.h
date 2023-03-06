#pragma once

using IndexType = std::uint32_t;

struct SFace
{
	IndexType a;
	IndexType b;
	IndexType c;

	IndexType& operator[](IndexType i)
	{
		if (i >= 0 && i < sizeof(SFace) / sizeof(IndexType))
			return *(reinterpret_cast<IndexType*>(this) + i);
		else
			throw("[] out of range.");
	}

	const IndexType& operator[](IndexType i) const
	{
		if (i >= 0 && i < sizeof(SFace) / sizeof(IndexType))
			return *(reinterpret_cast<const IndexType*>(this) + i);
		else
			throw("[] out of range.");
	}

	IndexType& at(IndexType i) { return operator[](i); }
	const IndexType& at(IndexType i) const { return operator[](i); }
};