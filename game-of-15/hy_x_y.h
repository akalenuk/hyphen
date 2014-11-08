#ifndef HY_X_Y_H_INCLUDED
#define HY_X_Y_H_INCLUDED

#include "hy_blend.h"

struct X_x{} x;
int operator-(string name, X_x x_x){
    return static_cast<int>(context::get_thing(name).real_x);
}

struct X_y{} y;
int operator-(string name, X_y x_x){
    return static_cast<int>(context::get_thing(name).real_y);
}

#endif // HY_X_Y_H_INCLUDED
