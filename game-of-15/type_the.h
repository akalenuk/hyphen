#ifndef TYPE_THE_H_INCLUDED
#define TYPE_THE_H_INCLUDED

#include <string>
#include <vector>
#include <stdexcept>

#include <cstdlib> // for atoi
#include <sstream> // for sstream


class the // runtime_error for type errors
{
    enum class Type {Int, String, Vector, Undefined};
    Type m_type = Type::Undefined;
    int m_int = 0;
    std::string m_string;
    std::vector<the> m_vector;

public:
    the() : m_type{Type::Undefined}, m_int{0}, m_string{}, m_vector{} {}
    the(const int i) : m_type{Type::Int}, m_int{i}, m_string{}, m_vector{} {}
    the(const char* s) : m_type{Type::String}, m_int{0}, m_string{s}, m_vector{} {}
    the(const std::string& s) : m_type{Type::String}, m_int{0}, m_string{s}, m_vector{} {}
    the(const std::initializer_list<the>& v) : m_type{Type::Vector}, m_int{0}, m_string{}, m_vector{v.begin(), v.end()} {}

    operator int(){
        if(m_type == Type::Int){
            return m_int;
        }else if(m_type == Type::String){
            //return std::stoi(m_string);
            return atoi(m_string.c_str());
        }
        throw std::runtime_error("This 'the' variable is not single.");
    }

    operator std::string(){
        if(m_type == Type::String){
            return m_string;
        }else if(m_type == Type::Int){
            //return std::to_string(m_int);
            std::stringstream ss;
            ss << m_int;
            return ss.str();
        }
        throw std::runtime_error("This 'the' variable is not single.");
    }

    the operator&(the b){
        if(m_type == Type::String){
            if(b.m_type == Type::String){
                return the(m_string + b.m_string);
            }else if(b.m_type == Type::Int){
                return the(m_string + static_cast<std::string>(b));
            }
        }
        throw std::runtime_error("& for 'the' works only with single strings.");
    }

    the operator[](int i){
        if(m_type == Type::Vector){
            return m_vector.at(i-1);
        }
        throw std::runtime_error("This 'the' doesn't hold multiple values.");
    }

    std::vector<the>::iterator begin(){
        return m_vector.begin();
    }

    std::vector<the>::iterator end(){
        return m_vector.end();
    }
};

the operator&(const std::string& a, the b){
    return the(a) & b;
}

#endif // TYPE_THE_H_INCLUDED
