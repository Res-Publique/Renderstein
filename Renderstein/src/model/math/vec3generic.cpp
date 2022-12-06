#include "vec3generic.h"

std::istream &operator >>(std::istream &istream, vec3& vec){
    return istream >> vec.x >> vec.y >> vec.z;
}
