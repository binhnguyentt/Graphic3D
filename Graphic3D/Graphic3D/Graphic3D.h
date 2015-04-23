#ifndef __Graphic3D_h_included__
#define __Graphic3D_h_included__

#include <iostream>
#include <list>
#include <windows.h>

#include "../Math/Vec4.hpp"
#include "../Math/Mat4.hpp"

enum class DrawType
{
    LINE_STRIP
};

struct VerticesData
{
    DrawType type;
    std::list<Vec4f> data;
};

class Graphic3D
{
protected:
    HWND m_hWnd;
    HBITMAP m_hBitmap;
    HDC m_hDC, m_hMemDC;
    int m_width, m_height;

    Mat4f m_Model;
    Mat4f m_View;
    Mat4f m_Projection;
    Mat4f m_MVP;

    std::list<VerticesData> m_lstVertices;

    Vec4f _process(const Vec4f& vec);

public:
    Graphic3D(HWND hWnd);
    ~Graphic3D();

    void vertices(DrawType type, const std::list<Vec4f>& data);

    void update(float dt);
    void render();
};

#endif // __Graphic3D_h_included__