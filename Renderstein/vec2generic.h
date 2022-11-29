#ifndef VEC2GENERIC_H
#define VEC2GENERIC_H

#include <iostream>

template<typename T>
class Vec2Generic
{
public:
    Vec2Generic();
    T x;
    T y;
};

using vec2 = Vec2Generic<float>;


// Implementations


template<typename T>
Vec2Generic<T>::Vec2Generic()
{

}






std::istream &operator >>(std::istream &istream, vec2& vec);
#endif // VEC2GENERIC_H
