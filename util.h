#ifndef UTIL_H
#define UTIL_H

#include <sstream>

template<typename T>
inline string str(const T& v){
    std::ostringstream iss;
    iss << v;
    return iss.str();
}

#endif
