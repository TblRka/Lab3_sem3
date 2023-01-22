#ifndef SUP_H
#define SUP_H
#include <limits>
#include <string>

template <typename T>
struct sup 
{
    T operator()() 
    {
        return std::numeric_limits<int>::max();
    }
};

#endif // SUP_H
