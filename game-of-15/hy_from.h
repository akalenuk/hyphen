#ifndef HY_FROM_H_INCLUDED
#define HY_FROM_H_INCLUDED

#include "hy_mouse.h"

struct From_a_to_X{
    int m_a;
    From_a_to_X(int a) : m_a(a) {}
    vector<int> operator-(int b){  // assert range here!
        vector<int> i(b - m_a + 1);
        iota(i.begin(), i.end(), m_a);
        return i;
    }
};

struct From_a_X{
    int m_a;
    From_a_X(int a) : m_a(a) {}
    From_a_to_X operator-(To to){
        return From_a_to_X(m_a);
    }
};

struct From_X{
    From_a_X operator-(int a){
        return From_a_X(a);
    }
} from;

#endif // HY_FROM_H_INCLUDED
