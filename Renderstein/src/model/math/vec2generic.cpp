#include "vec2generic.h"

std::istream &operator >>(std::istream &istream, vec2& vec){
    return istream >> vec.x >> vec.y;
}
