#ifndef __Vec4_hpp_included__
#define __Vec4_hpp_included__

#include <cmath>
#include "../Common.hpp"

template <typename T>
class Vec4
{
protected:
    T m_x, m_y, m_z, m_w;

public:
    /**
    * Copy constructor
    */
    Vec4(const Vec4& vec)
    {
        m_x = vec.x();
        m_y = vec.y();
        m_z = vec.z();
        m_w = vec.w();
    }

    Vec4(T x, T y, T z, T w)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_w = w;
    }

    Vec4()
        :m_x(0), m_y(0), m_z(0), m_w(0)
    {
    }

    inline T x() const
    {
        return m_x;
    }

    inline T y() const
    {
        return m_y;
    }

    inline T z() const
    {
        return m_z;
    }

    inline T w() const
    {
        return m_w;
    }

    inline Vec4& x(T num)
    {
        m_x = num;
        return *this;
    }

    inline Vec4& y(T num)
    {
        m_y = num;
        return *this;
    }

    inline Vec4& z(T num)
    {
        m_z = num;
        return *this;
    }

    inline Vec4& w(T num)
    {
        m_w = num;
        return *this;
    }

    Vec4 operator +(const Vec4& vec) const
    {
        return Vec4(m_x + vec.x(), m_y + vec.y(), m_z + vec.z(), m_w + vec.w());
    }

    Vec4 operator -(const Vec4& vec) const
    {
        return Vec4(m_x - vec.x(), m_y - vec.y(), m_z - vec.z(), m_w - vec.w());
    }

    Vec4 operator *(const T factor) const
    {
        return Vec4(m_x * factor, m_y * factor, m_z * factor, m_w * factor);
    }

    Vec4 operator /(const T factor) const
    {
        return Vec4(m_x / factor, m_y / factor, m_z / factor, m_w / factor);
    }

    Vec4& operator +=(const Vec4& vec)
    {
        m_x += vec.x();
        m_y += vec.y();
        m_z += vec.z();
        m_w += vec.w();

        return *this;
    }

    Vec4& operator -=(const Vec4& vec)
    {
        m_x -= vec.x();
        m_y -= vec.y();
        m_z -= vec.z();
        m_w -= vec.w();

        return *this;
    }

    Vec4& operator *=(const T factor)
    {
        m_x *= factor;
        m_y *= factor;
        m_z *= factor;
        m_w *= factor;

        return *this;
    }

    Vec4& operator /=(const T factor)
    {
        m_x /= factor;
        m_y /= factor;
        m_z /= factor;
        m_w /= factor;

        return *this;
    }

    bool operator ==(const Vec4 vec)
    {
        if ((m_x == vec.x()) && (m_y == vec.y()) && (m_z == vec.z()) && (m_w == vec.w()))
            return true;
        
        return false;
    }

    T length() const
    {
        return std::sqrt(SQR(m_x) + SQR(m_y) + SQR(m_z) + SQR(m_w));
    }

    Vec4 nomalize() const
    {
        T len = length();
        return Vec4(m_x/len, m_y/len, m_z/len, m_w/len);
    }
};

typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;

#endif // __Vec4_hpp_included__