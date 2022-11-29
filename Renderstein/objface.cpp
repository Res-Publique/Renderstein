#include "objface.h"
#include "sstream"

ObjFace::ObjFace()
{

}

int countOfSpaces(std::string &s) {
    auto counter = 0;
    for (auto c: s) {
        counter += c == ' ';
    }
    return counter;
}

std::istream &operator >>(std::istream &istream, ObjFace& face) {
    int v, vt = -1, vn = -1;
    std::string s, line;
    static auto dash = "/";
    std::getline(istream, line);
    std::stringstream ss(line);
    auto spacesCount = countOfSpaces(line);
    while (ss >> s) {
        int i = s.find(dash);
        int j = s.find_last_of(dash);
        if (i == std::string::npos) {
            // v
            v = std::stoi(s) - 1;
        } else if (i == j) {
            // v/vt
            v = std::stoi(s.substr(0, i)) - 1;
            vt = std::stoi(s.substr(i + 1));
        } else if (i == j - 1) {
            // v//vn
            v = std::stoi(s.substr(0, i)) - 1;
            vn = std::stoi(s.substr(i + 2));
        } else {
            // v/vt/vn
            v = std::stoi(s.substr(0, i)) - 1;
            vt = std::stoi(s.substr(i + 1, j));
            vn = std::stoi(s.substr(j + 1));
        }
        face.v.push_back(v);
        face.vt.push_back(vt);
        face.vn.push_back(vn);
    }
    return istream;
}
