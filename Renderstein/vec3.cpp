#include "vec3.h"

#include <istream>

vec3::vec3()
{

}

std::istream &operator >>(std::istream &istream, vec3& vec) {
    return istream >> vec.x >> vec.y >> vec.z;
}
