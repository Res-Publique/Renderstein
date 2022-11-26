#ifndef VEC2_H
#define VEC2_H

#include <istream>



class vec2
{
public:
    vec2();
    float x;
    float y;
};

std::istream &operator >>(std::istream &istream, vec2& vec);

#endif // VEC2_H
