#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "hge.h"
#include "thing.h"
#include <vector>
#include <map>
#include <string>

namespace context{
    using namespace std;

    HGE* get_hge();
    void set_hge(HGE* hge);
    void add_thing(string name, Thing& thing);
    vector<Thing>& get_things();
    Thing& get_thing(string name);
}
#endif // CONTEXT_H_INCLUDED
