#include "context.h"
#include <vector>
#include <map>
#include <string>


namespace context{
    using namespace std;
    static HGE* n_hge;
    vector<Thing> m_things;
    map<string, int> m_name_to_thing_index;

    HGE* get_hge(){
        return n_hge;
    }
    void set_hge(HGE* hge){
        n_hge = hge;
    }

    void add_thing(string name, Thing& thing){    // add error handling
        m_name_to_thing_index[name] = m_things.size();
        m_things.push_back(thing);
    }
    vector<Thing>& get_things(){
        return m_things;
    }
    Thing& get_thing(string name){
        return m_things[m_name_to_thing_index[name]];
    }
}

