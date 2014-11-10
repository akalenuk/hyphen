#ifndef HYPHEN_H_INCLUDED
#define HYPHEN_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <unordered_map>

#include "type_the.h"

namespace hyphen{
    the it = 0;

    // print-"Hello world!"
    struct Print_X{
        void operator-(the t) {
            std::cout << static_cast<std::string>(t) << std::endl;
            it = t;
        }
    } print;

    // the Numbers = split-"12, 34, 5, 67, 8"-with-", ";
    struct With {} with;
    struct a_Split_with_X{
        the m_a;
        a_Split_with_X(the a) : m_a(a) {}
        the operator-(the b){
            return m_a.split_with(b);
        }
    };
    struct a_Split_X{
        the m_a;
        a_Split_X(the a) : m_a(a) {}
        a_Split_with_X operator-(With with){
            return a_Split_with_X(m_a);
        }
    };
    struct X_Split{
    } split;
    a_Split_X operator-(the a, X_Split x_split){
        return a_Split_X(a);
    }

    // the String = Numbers-joined-with-" ";
    struct a_Joined_with_X{
        the m_a;
        a_Joined_with_X(the a) : m_a(a) {}
        the operator-(the b){
            return m_a.joined_with(b);
        }
    };
    struct a_Joined_X{
        the m_a;
        a_Joined_X(the a) : m_a(a) {}
        a_Joined_with_X operator-(With with){
            return a_Joined_with_X(m_a);
        }
    };
    struct X_Joined{
    } joined;
    a_Joined_X operator-(the a, X_Joined x_joined){
        return a_Joined_X(a);
    }

    // Name-in-quotes
    struct Quotemarks {} quotemarks;

    struct string_in_X{
        std::string m_string;
        string_in_X(std::string s) : m_string(s) {}
        std::string operator-(Quotemarks quotemarks){
            return std::string("\"") + m_string + "\"";
        }
    };

    struct X_In {} in;

    string_in_X operator-(std::string s, X_In x_in) {
        return string_in_X(s);
    }

    // for(the I : from-1-to-9)
    struct To {} to;
    struct From_a_to_X{
        int m_a;
        From_a_to_X(int a) : m_a(a) {}
        std::vector<int> operator-(int b){  // assert range here!
            std::vector<int> i(b - m_a + 1);
            std::iota(i.begin(), i.end(), m_a);
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

    // the FirstThree = Numbers-elements-(from-1-to-3);
    struct t_Elements_X{
        the m_t;
        t_Elements_X(the t) : m_t(t) {}
        the operator-(the indexes){
            std::vector<the> to;
            for(int i : indexes){
                to.push_back(m_t[i]);
            }
            return the(to);
        }
    };
    struct X_Elements{
    } elements;
    t_Elements_X operator-(the t, X_Elements elements){
        return t_Elements_X(t);
    }

    // if( size-of-FirstThree != 3 )
    struct Of {} of;
    struct Size_of_X{
        size_t operator-(the t){
            return t.size();
        }
    };
    struct Size_X {
        Size_of_X operator-(Of of){
            return Size_of_X();
        }
    } size, last;

    // save-"Hello, file!"-to-"file.txt";
    struct Save_t_to_X{
        the m_t;
        Save_t_to_X(the t) : m_t(t) {}
        void operator-(std::string path){   // assert type and file
            std::ofstream ofs(path);
            ofs << static_cast<std::string>(m_t);
            it = m_t;
        }
    };
    struct Save_t_X{
        the m_t;
        Save_t_X(the t) : m_t(t) {}
        Save_t_to_X operator-(To to){
            return Save_t_to_X(m_t);
        }
    };
    struct Save_X{
        Save_t_X operator-(the t){
            return Save_t_X(t);
        }
    } save;

    // the Text = loaded-from-"file.txt"
    struct Loaded_from_X{
        std::string operator-(std::string path){   // assert type and file
            std::ifstream ifs(path);
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            return std::string(buffer.str());
        }
    };
    struct Loaded_X{
        Loaded_from_X operator-(From_X from){
            return Loaded_from_X();
        }
    } loaded;

    // memorize-"2-12-85-06"-as-"Tel"
    std::unordered_map<std::string, the> memory;

    struct As {} as;

    struct Memorize_text_as_X{
        the m_value;
        Memorize_text_as_X(the value) : m_value(value) {}
        void operator-(std::string key){
            memory[key] = m_value;
            it = m_value;
        }
    };
    struct Memorize_text_X{
        the m_value;
        Memorize_text_X(the value) : m_value(value) {}
        Memorize_text_as_X operator-(As as){
            return Memorize_text_as_X(m_value);
        }
    };
    struct Memorize_X{
        Memorize_text_X operator-(the value){
            memory[value] = 0;
            it = value;
            return Memorize_text_X(value);
        }
    } memorize;

    // remember-"Tel"
    struct Remember_X{
        bool operator-(std::string key){
            it = key;
            return memory.find(key) != memory.end();
        }
    } remember;

    // remembered-as-"Tel"
    struct Remembered_as_X{
        the operator-(std::string key){
            return memory[key];
        }
    };
    struct Remembered_X{
        Remembered_as_X operator-(As as){
            return Remembered_as_X();
        }
    } remembered;

}

#endif // HYPHEN_H_INCLUDED
