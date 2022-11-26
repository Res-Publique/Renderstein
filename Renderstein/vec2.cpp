#include "vec2.h"

vec2::vec2()
{

}

std::istream &operator >>(std::istream &istream, vec2& vec) {
    return istream >> vec.x >> vec.y;
}
