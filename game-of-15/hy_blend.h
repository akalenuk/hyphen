#ifndef HY_BLEND_H_INCLUDED
#define HY_BLEND_H_INCLUDED

#include "hy_slide.h"

#include "thing.h"

struct Solid{} solid;
struct Glassy{} glassy;

struct Blend_name_X{
    string m_name;
    Blend_name_X(string name) : m_name{name} {}
    void operator-(Glassy glassy){
        context::get_thing(m_name).Blend(BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE);
        it = m_name;
    }
    void operator-(Solid solid){
        context::get_thing(m_name).Blend(BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE);
        it = m_name;
    }
};

struct Blend_X{
    Blend_name_X operator-(string X){
        return Blend_name_X(X);
    }
} blend;

#endif // HY_BLEND_H_INCLUDED
