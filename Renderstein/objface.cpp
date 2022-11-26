#include "objface.h"
#include "sstream"

ObjFace::ObjFace()
{

}

std::istream &operator >>(std::istream &istream, ObjFace& face) {
    int v, vt = -1, vn = -1;
    std::string s, line;
    static auto dash = "/";
    std::getline(istream, line);
    std::stringstream ss(line);
    while (ss >> s) {
        int i = s.find(dash);
        int j = s.find_last_of(dash);
        if (i == std::string::npos) {
            // v
            v = std::stoi(s);
        } else if (i == j) {
            // v/vt
            v = std::stoi(s.substr(0, i));
            vt = std::stoi(s.substr(i + 1));
        } else if (i == j - 1) {
            // v//vn
            v = std::stoi(s.substr(0, i));
            vn = std::stoi(s.substr(i + 2));
        } else {
            // v/vt/vn
            v = std::stoi(s.substr(0, i));
            vt = std::stoi(s.substr(i + 1, j));
            vn = std::stoi(s.substr(j + 1));
        }
        face.v.push_back(v);
        face.vt.push_back(vt);
        face.vn.push_back(vn);
    }
    return istream;
}
