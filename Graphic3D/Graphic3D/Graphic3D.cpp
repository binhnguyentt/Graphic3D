#include "Graphic3D.h"

Graphic3D::Graphic3D(HWND hWnd)
{
    m_hWnd = hWnd;

    RECT rc;
    GetClientRect(m_hWnd, &rc);
    m_width = rc.right - rc.left;
    m_height = rc.bottom - rc.top;

    m_hDC = GetDC(m_hWnd);
    m_hBitmap = CreateCompatibleBitmap(m_hDC, m_width, m_height);
    m_hMemDC = CreateCompatibleDC(m_hDC);
    SelectObject(m_hMemDC, m_hBitmap);

    // SelectObject(m_hMemDC, GetStockObject(WHITE_BRUSH));
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(m_hMemDC, hPen);

    // Setup matrices
    m_Model.setIdentity();
    m_View.setIdentity();
    m_Projection.setIdentity();
    m_MVP.setIdentity();
}

Graphic3D::~Graphic3D()
{
    ReleaseDC(m_hWnd, m_hDC);
}

void Graphic3D::update(float dt)
{
    
}

void Graphic3D::render()
{
    auto beg = m_lstVertices.begin();
    auto end = m_lstVertices.end();

    for (auto i=beg; i!=end; ++i)
    {
        VerticesData& packet = *i;

        switch (packet.type) 
        {
        case DrawType::LINE_STRIP:
        {
            if (packet.data.size() < 2) break;

            auto b = packet.data.begin();
            auto e = packet.data.end();
            auto j = b;
            j++;

            auto p = _process(*b);
            MoveToEx(m_hMemDC, p.x(), p.y(), NULL);
            for (; j != e; ++j)
            {
                p = _process(*j);
                LineTo(m_hMemDC, p.x(), p.y());
            }
            break;
        }

        default:
            break;
        }
    }

    BitBlt(m_hDC, 0, 0, m_width, m_height, m_hMemDC, 0, 0, SRCCOPY);
}

void Graphic3D::vertices(DrawType type, const std::list<Vec4f>& data)
{
    VerticesData packet;

    packet.type = type;
    packet.data = data;
    m_lstVertices.push_back(packet);
}

Vec4f Graphic3D::_process(const Vec4f& vec)
{
    auto rs = m_MVP * vec;

    auto _w2 = m_width / 2.0f;
    auto _y2 = m_height / 2.0f;

    auto sx = rs.x() * _w2;
    auto sy = rs.y() * _y2;

    auto _x = sx + _w2;
    auto _y = sy + _y2;

    rs.x(_x);
    rs.y(_y);
    return rs;
}
