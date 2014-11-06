#ifndef HY_MOUSE_H_INCLUDED
#define HY_MOUSE_H_INCLUDED

#include "hy_blend.h"

struct X {} x;
struct Y {} y;

struct Mouse_X{
    float m_x;
    float m_y;
    int operator-(X x){
        context::get_hge()->Input_GetMousePos(&m_x, &m_y);
        return static_cast<int>(m_x);
    }
    int operator-(Y y){
        context::get_hge()->Input_GetMousePos(&m_x, &m_y);
        return static_cast<int>(m_y);
    }
} mouse;

#endif // HY_MOUSE_H_INCLUDED
