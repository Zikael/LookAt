#ifndef __VECTOR
#define __VECTOR

template <typename T>
class Vector
{
private:
	T babylonianSqrt(const T n)
	{
		T est = 10;
		for (int itr = 0; itr < 10; ++itr)
		{
			est = (est + (n / est)) / 2;
		}
		return est;
	}
public:

	struct Vect3D {
		T x, y, z;

		Vect3D() noexcept
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vect3D(T x, T y, T z) noexcept
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vect3D& operator-(const Vect3D& v) noexcept
		{
			return Vect3D(x - v.x, y - v.y, z - v.z);
		}

		Vect3D& operator+(const Vect3D& v) noexcept
		{
			return Vect3D(x + v.x, y + v.y, z + v.z);
		}

		Vect3D& operator+=(const Vect3D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vect3D& operator-=(const Vect3D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		bool operator==(const Vect3D& v) noexcept
		{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const Vect3D& v) noexcept
		{
			return x != v.x || y != v.y || z != v.z;
		}
	};

	Vector() noexcept { /* Empty */ }

	inline T dotproduct(const Vect3D v1, const Vect3D v2) noexcept
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	inline Vect3D& crossproduct(const Vect3D v1, const Vect3D v2) noexcept
	{
		return Vect3D(
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x)
		);
	}

	inline T getUnitVector(const Vect3D v) noexcept
	{
		return babylonianSqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	inline Vect3D& normalise(const Vect3D v) noexcept
	{
		const T unit = getUnitVector(v);
		return Vect3D(v.x / unit, v.y / unit, v.z / unit);
	}
};

#endif