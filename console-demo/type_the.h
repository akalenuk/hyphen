#ifndef TYPE_THE_H_INCLUDED
#define TYPE_THE_H_INCLUDED

#include <string>
#include <vector>
#include <stdexcept>

#include <cstdlib> // for atoi
#include <sstream> // for sstream

namespace hyphen{
    class the // runtime_error for type errors
    {
        enum class Type {Int, String, Vector, Undefined};
        Type m_type = Type::Undefined;
        int m_int = 0;
        std::string m_string;
        std::vector<the> m_vector;

    public:
        the() : m_type{Type::Undefined}, m_int{0}, m_string{}, m_vector{} {}
        the(int i) : m_type{Type::Int}, m_int{i}, m_string{}, m_vector{} {}
        the(const std::string& s) : m_type{Type::String}, m_int{0}, m_string{s}, m_vector{} {}
        the(const char* s) : the(std::string(s)) {}
        the(const std::vector<the>& v) : m_type{Type::Vector}, m_int{0}, m_string{}, m_vector{v.begin(), v.end()} {}
        the(const std::vector<int>& v) : m_type{Type::Vector}, m_int{0}, m_string{}, m_vector{v.begin(), v.end()} {}
        the(const std::initializer_list<the>& v) : the(static_cast<std::vector<the> >(v)) {}

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
            }else{
                return this->joined_with(", ");
            }
        }

        the operator&(the b){
            if(m_type == Type::String){
                if(b.m_type == Type::String){
                    return the(m_string + b.m_string);
                }else if(b.m_type == Type::Int){
                    return the(m_string + static_cast<std::string>(b));
                }
            }else if(m_type == Type::Int){
                if(b.m_type == Type::String){
                    return the(static_cast<std::string>(*this) + b.m_string);
                }else if(b.m_type == Type::Int){
                    return the(static_cast<std::string>(*this) + static_cast<std::string>(b));
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

        the split_with(the coma){
            if(m_type == Type::String && coma.m_type == Type::String ){
                std::vector<the> to;
                size_t coma_pos = 0;
                size_t coma_len = coma.m_string.size();
                while(coma_pos != std::string::npos){
                    size_t new_coma_pos = m_string.find(coma.m_string, coma_pos);
                    if(new_coma_pos != std::string::npos){
                        to.push_back(m_string.substr(coma_pos, new_coma_pos - coma_pos));
                        coma_pos = new_coma_pos + coma_len;
                    }else{
                        to.push_back(m_string.substr(coma_pos, std::string::npos));
                        coma_pos = std::string::npos;
                    }
                }
                return the(to);
            }else{
                throw std::runtime_error("Split works with strings only.");
            }
        }

        the joined_with(the coma){
            if(m_type == Type::Vector && coma.m_type == Type::String && !m_vector.empty()){
                the to = m_vector.front();
                std::vector<the>::iterator it = m_vector.begin();
                std::vector<the>::iterator eit = m_vector.end();
                for(++it; it != eit; ++it){
                    to = to & coma & (*it);
                }
                return to;
            }
            throw std::runtime_error("Join works with multiple strings on the left and single strings on the right.");
        }

        std::vector<the>::iterator begin(){
            return m_vector.begin();
        }

        std::vector<the>::iterator end(){
            return m_vector.end();
        }

        size_t size(){
            if(m_type == Type::Vector){
                return m_vector.size();
            }
            throw std::runtime_error("Size works only on multiple values.");
        }

        void append(the t){
            if(m_type == Type::Undefined){
                m_type = Type::Vector;
                this->append(t);
            }else if(m_type == Type::Vector){
                if(t.m_type == Type::Vector){
                    m_vector.insert(m_vector.end(), t.m_vector.begin(), t.m_vector.end());
                }else{
                    m_vector.push_back(t);
                }
            }else{
                throw std::runtime_error("Append works only on multiple values or completely new 'the'.");
            }
        }
    };

    the operator&(const std::string& a, the b){
        return the(a) & b;
    }
}
#endif // TYPE_THE_H_INCLUDED
