#ifndef HY_SLIDE_H_INCLUDED
#define HY_SLIDE_H_INCLUDED

#include "hy_teleport.h"

#include "thing.h"

struct In {} in;
struct Ms {} ms;

struct Slide_name_to_x_y_in_ms_X{
    string m_name;
    int m_x;
    int m_y;
    int m_ms;
    Slide_name_to_x_y_in_ms_X(string name, int x, int y, int ms) : m_name{name}, m_x{x}, m_y{y}, m_ms{ms} { }
    void operator-(Ms ms){
        context::get_thing(m_name).Slide(m_x, m_y, m_ms);
        it = m_name;
    }
};

struct Slide_name_to_x_y_in_X{
    string m_name;
    int m_x;
    int m_y;
    Slide_name_to_x_y_in_X(string name, int x, int y) : m_name{name}, m_x{x}, m_y{y} { }
    Slide_name_to_x_y_in_ms_X operator-(int ms){
        return Slide_name_to_x_y_in_ms_X(m_name, m_x, m_y, ms);
    }
};

struct Slide_name_to_x_y_X{
    string m_name;
    int m_x;
    int m_y;
    Slide_name_to_x_y_X(string name, int x, int y) : m_name{name}, m_x{x}, m_y{y} { }
    Slide_name_to_x_y_in_X operator-(In in){
        return Slide_name_to_x_y_in_X(m_name, m_x, m_y);
    }
};

struct Slide_name_to_x_X{
    string m_name;
    int m_x;
    Slide_name_to_x_X(string name, int x) : m_name{name}, m_x{x} { }
    Slide_name_to_x_y_X operator-(int y){
        return Slide_name_to_x_y_X(m_name, m_x, y);
    }
};

struct Slide_name_on_X{
    string m_name;
    Slide_name_on_X(string name) : m_name{name} { }
    Slide_name_to_x_y_X operator-(string to_name){
        Thing& thing = context::get_thing(to_name);
        return Slide_name_to_x_y_X(m_name, thing.real_x, thing.real_y);
    }
};

struct Slide_name_to_X{
    string m_name;
    Slide_name_to_X(string name) : m_name{name} { }
    Slide_name_to_x_X operator-(int x){
        return Slide_name_to_x_X(m_name, x);
    }
};

struct Slide_name_X{
    string m_name;
    Slide_name_X(string name) : m_name{name} {}
    Slide_name_to_X operator-(To to){
        return Slide_name_to_X(m_name);
    }
    Slide_name_on_X operator-(On on){
        return Slide_name_on_X(m_name);
    }
};

struct Slide_X{
    Slide_name_X operator-(string X){
        return Slide_name_X(X);
    }
} slide;

#endif // HY_SLIDE_H_INCLUDED
