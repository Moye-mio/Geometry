#pragma once

#include <stdexcept>

using DataType				= float;
using IndexType				= unsigned int;

class Vector3f
{
public:
	DataType x = 0;
	DataType y = 0;
	DataType z = 0;

	Vector3f() = default;
	Vector3f(const Vector3f& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	Vector3f(Vector3f&& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	Vector3f(DataType vx, DataType vy, DataType vz)
	{
		x = vx;
		y = vy;
		z = vz;
	}

	~Vector3f() = default;

	DataType& operator[](IndexType i)
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::runtime_error("Out of Index");
		}
	}

	const DataType& operator[](IndexType i) const
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::runtime_error("Out of Index");
		}
	}

	bool operator == (const Vector3f& v) const
	{
		if (x == v.x && y == v.y && z == v.z)	return true;
		else									return false;
	}

	DataType norm()
	{
		return std::sqrtf(x * x + y * y + z * z);
	}
};