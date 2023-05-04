#include <cmath>
struct vec2
{
	float x, y;
};

float ToMeters(float x)
{
	return x / 39.62f;
}

struct Rotator
{
	float Pitch, Yaw, Roll;
};

struct Vector3
{
	float x, y, z;
	Vector3 operator-(Vector3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	Vector3 operator+(Vector3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	Vector3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	Vector3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	Vector3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	Vector3 operator+=(Vector3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	Vector3 operator-=(Vector3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(Vector3 ape)
	{
		return (*this - ape).Length2D();
	}

	float Dot(Vector3& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
};
struct Vector4
{
	float w, x, y, z;
};