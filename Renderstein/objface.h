#ifndef OBJFACE_H
#define OBJFACE_H

#include <istream>
#include <vector>

class ObjFace
{
public:
    ObjFace();
    std::vector<int> v;
    std::vector<int> vt;
    std::vector<int> vn;
};

std::istream &operator >>(std::istream &istream, ObjFace& face);

#endif // OBJFACE_H
