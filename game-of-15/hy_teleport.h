#ifndef HY_TELEPORT_H_INCLUDED
#define HY_TELEPORT_H_INCLUDED


#include "hy_load.h"

#include "thing.h"

struct To{} to;
struct On {} on;

struct Teleport_name_to_x_X{
    string m_name;
    int m_x;
    Teleport_name_to_x_X(string name, int x) : m_name{name}, m_x{x} { }
    void operator-(int y){
        context::get_thing(m_name).Teleport(m_x, y);
        it = m_name;
    }
};

struct Teleport_name_to_X{
    string m_name;
    Teleport_name_to_X(string name) : m_name{name} { }
    Teleport_name_to_x_X operator-(int x){
        return Teleport_name_to_x_X(m_name, x);
    }
};

struct Teleport_name_on_X{
    string m_name;
    Teleport_name_on_X(string name) : m_name{name} { }
    void operator-(string to_name){
        Thing& thing = context::get_thing(to_name);
        context::get_thing(m_name).Teleport(thing.real_x, thing.real_y);
        it = m_name;
    }
};

struct Teleport_name_X{
    string m_name;
    Teleport_name_X(string name) : m_name{name} {}
    Teleport_name_to_X operator-(To to){
        return Teleport_name_to_X(m_name);
    }
    Teleport_name_on_X operator-(On on){
        return Teleport_name_on_X(m_name);
    }
};

struct Teleport_X{
    Teleport_name_X operator-(string X){
        return Teleport_name_X(X);
    }
} teleport;


#endif // HY_TELEPORT_H_INCLUDED
