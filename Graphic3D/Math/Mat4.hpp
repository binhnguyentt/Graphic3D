#ifndef __Mat4_hpp_included__
#define __Mat4_hpp_included__

#include "Vec4.hpp"

/**
 * Matrix 4x4 column major
 */
template <typename T>
class Mat4
{
protected:
    T m[16];

public:
    Mat4(const Mat4& mat)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)[i][j] = mat[i][j];
            }
        }
    }

    Mat4()
    {
        m[0] = 0; m[1] = 0; m[2] = 0; m[3] = 0;
        m[4] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
        m[8] = 0; m[9] = 0; m[10] = 0; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 0;
    }

    inline const T* data() const
    {
        return &m[0];
    }

    inline T* data()
    {
        return &m[0];
    }

    T* operator [](int row)
    {
        return &m[row * 4];
    }

    const T* operator [](int row) const
    {
        return &m[row * 4];
    }

    Mat4& setIdentity()
    {
        m[0]  = 1; m[1]  = 0; m[2]  = 0; m[3]  = 0; 
        m[4]  = 0; m[5]  = 1; m[6]  = 0; m[7]  = 0; 
        m[8]  = 0; m[9]  = 0; m[10] = 1; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

        return *this;
    }

    Mat4 transpose()
    {
        Mat4 rs;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; j++) {
                rs[j][i] = (*this)[i][j];
            }
        }

        return rs;
    }

    Mat4 operator *(const float factor) const
    {
        Mat4 rs;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                rs[i][j] = (*this)[i][j] * factor;
            }
        }

        return rs;
    }

    Mat4 operator /(const float factor) const
    {
        Mat4 rs;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                rs[i][j] = (*this)[i][j] / factor;
            }
        }

        return rs;
    }

    Mat4 operator +(T num) const
    {
        Mat4 rs;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                rs[i][j] = (*this)[i][j] + num;
            }
        }

        return rs;
    }

    Mat4 operator -(T num) const
    {
        Mat4 rs;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                rs[i][j] = (*this)[i][j] - num;
            }
        }

        return rs;
    }

    Mat4 operator *(const Mat4& mat) const
    {
        Mat4 rs;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; k++) {
                    rs[i][j] += (*this)[i][k] * mat[k][j];
                }
            }
        }

        return rs;
    }

    template <typename K>
    Vec4<K> operator *(const Vec4<K>& vec) const
    {
        Mat4& t = const_cast<Mat4&>(*this);

        K _x = vec.x()*t[0][0] + vec.y()*t[0][1] + vec.z()*t[0][2] + vec.w()*t[0][3];
        K _y = vec.x()*t[1][0] + vec.y()*t[1][1] + vec.z()*t[1][2] + vec.w()*t[1][3];
        K _z = vec.x()*t[2][0] + vec.y()*t[2][1] + vec.z()*t[2][2] + vec.w()*t[2][3];
        K _w = vec.x()*t[3][0] + vec.y()*t[3][1] + vec.z()*t[3][2] + vec.w()*t[3][3];

        return Vec4<K>(_x, _y, _z, _w);
    }
};

typedef Mat4<float> Mat4f;

#endif // __Mat4_hpp_included__