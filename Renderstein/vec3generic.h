#ifndef VEC3GENERIC_H
#define VEC3GENERIC_H

#include <iostream>

template<typename T>
class Vec3Generic
{
public:
    Vec3Generic();
    T x;
    T y;
    T z;
};

using vec3 = Vec3Generic<float>;


// Implementations

template<typename T>
Vec3Generic<T>::Vec3Generic()
{

}




std::istream &operator >>(std::istream &istream, vec3& vec);


#endif // VEC3GENERIC_H
