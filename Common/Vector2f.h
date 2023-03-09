#pragma once

#include <stdexcept>

using DataType = float;
using IndexType = unsigned int;

class Vector2f
{
public:
	DataType x = 0;
	DataType y = 0;

	Vector2f() = default;
	Vector2f(const Vector2f& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	Vector2f(Vector2f&& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	Vector2f(float vx, float vy)
	{
		x = vx;
		y = vy;
	}

	~Vector2f() = default;

	DataType& operator[](IndexType i)
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
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
		default:
			throw std::runtime_error("Out of Index");
		}
	}

	DataType norm()
	{
		return std::sqrtf(x * x + y * y);
	}
};