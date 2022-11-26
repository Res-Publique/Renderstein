#ifndef VEC3_H
#define VEC3_H

#include <istream>

class vec3
{
public:
    vec3();
    float x;
    float y;
    float z;
};

std::istream &operator >>(std::istream &istream, vec3& vec);

#endif // VEC3_H
