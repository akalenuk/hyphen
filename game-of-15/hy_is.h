#ifndef HY_IS_H_INCLUDED
#define HY_IS_H_INCLUDED

#include "hy_mouse.h"

#include "thing.h"
#include "context.h"

struct Clicked {} clicked;

struct name_is_X{
    string m_name;
    name_is_X(string name) : m_name{name} {}
    bool operator-(Clicked clciked){
        if(context::get_hge()->Input_GetKeyState(HGEK_LBUTTON)){
            float mx;
            float my;
            context::get_hge()->Input_GetMousePos(&mx, &my);
            Thing by_name = context::get_thing(m_name);
            if( mx >= by_name.real_x and my >= by_name.real_y
            and mx < (by_name.real_x + by_name.w)
            and my < (by_name.real_y + by_name.h) ){
                return true;
            }
        }
        return false;
    }
};

struct X_is{
}is;

name_is_X operator-(string name, X_is x_is){
    it = name;
    return name_is_X(name);
}

#endif // HY_IS_H_INCLUDED
