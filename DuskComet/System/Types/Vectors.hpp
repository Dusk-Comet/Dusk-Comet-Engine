#ifndef DUSKCOMET_SYSTEM_TYPES_VECTORS__HPP
#define DUSKCOMET_SYSTEM_TYPES_VECTORS__HPP

#include <cstdint>

namespace dc
{

	template<class t>
	struct Vector2
	{
	public:
		t x = 0;
		t y = 0;

		Vector2()
		{

		}
		Vector2(t x, t y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2<t>& operator=(const Vector2<t>& obj)
		{
			if (Vector2<t>(this->x, this->y) == obj)
				return *this;

			this->x = obj.x;
			this->y = obj.y;
			return *this;
		}

		Vector2<t> operator+(const Vector2<t>& obj)
		{
			return Vector2<t>(this->x + obj.x, this->y + obj.y);
		}

		Vector2<t> operator-(const Vector2<t>& obj)
		{
			return Vector2<t>(this->x - obj.x, this->y - obj.y);
		}


		friend bool operator==(const Vector2<t>& objA, const Vector2<t>& objB)
		{
			return objA.x == objB.x && objA.y == objB.y;
		}


	};

	template<class t>
	struct Vector3
	{
	public:
		t x;
		t y;
		t z;

		Vector3()
		{

		}
		Vector3(t x, t y, t z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}
	};

	template<class t>
	struct Vector4
	{
	public:
		t x;
		t y;
		t z;
		t w;


		Vector4()
		{

		}

		Vector4(t x, t y, t z, t w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4(Vector2<t> source, t z, t w)
		{
			this->x = source.x;
			this->y = source.y;
			this->z = z;
			this->w = w;
		}

		Vector4(t x, t y, Vector2<t> source)
		{
			this->x = x;
			this->y = y;
			this->z = source.x;
			this->w = source.y;
		}

		Vector4(Vector2<t> sourceA, Vector2<t> sourceB)
		{
			this->x = sourceA.x;
			this->y = sourceA.y;
			this->z = sourceB.x;
			this->w = sourceB.y;
		}

		Vector4(Vector3<t> source, t w)
		{
			this->x = source.x;
			this->y = source.y;
			this->z = source.z;
			this->w = w;
		}
	};


	struct Color : Vector4<std::uint8_t>
	{
	public:

		inline void setR(const std::uint8_t& r)
		{
			this->x = r;
		}
		inline void setG(const std::uint8_t& g)
		{
			this->y = g;
		}
		inline void setB(const std::uint8_t& b)
		{
			this->z = b;
		}
		inline void setA(const std::uint8_t& a)
		{
			this->w = a;
		}

		inline std::uint8_t getR()
		{
			return this->x;
		}
		inline std::uint8_t getG()
		{
			return this->y;
		}
		inline std::uint8_t getB()
		{
			return this->z;
		}
		inline std::uint8_t getA()
		{
			return this->w;
		}

		Color() { }
		Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) { this->x = red; this->y = green; this->z = blue; this->w = alpha; }
		Color(const Color& src, std::uint8_t alpha) { this->x = src.x; this->y = src.y; this->z = src.z; this->w = alpha; }

	};

	typedef Vector2<std::uint8_t> Vector2ui8;
	typedef Vector2<std::int8_t> Vector2i8;

	typedef Vector2<std::uint16_t> Vector2ui16;
	typedef Vector2<std::int16_t> Vector2i16;

	typedef Vector2<std::uint32_t> Vector2ui32;
	typedef Vector2<std::int32_t> Vector2i32;

	typedef Vector2<std::uint64_t> Vector2ui64;
	typedef Vector2<std::int64_t> Vector2i64;

	typedef Vector4<std::int32_t> Rectangle;
	typedef Vector4<float> RectangleF;


	typedef Vector2<std::int32_t> Point;
	typedef Vector2<float> PointF;

	typedef Vector2<std::uint32_t> Size;

}

#endif // !DUSKCOMET_SYSTEM_TYPES_VECTORS__HPP