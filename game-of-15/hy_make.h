#ifndef HY_MAKE_H_INCLUDED
#define HY_MAKE_H_INCLUDED

#include "hy_it.h"

#include "thing.h"

struct Make_X{
    void operator-(string name){
        Thing new_one;
        new_one.visible = false;
        context::add_thing(name, new_one);
        it = name;
    }
} make;

#endif // HY_MAKE_H_INCLUDED
