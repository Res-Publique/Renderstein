#include "objparser.h"

#include <functional>
#include <map>


void parseVertex(ObjParserModel &model, std::istream &istream) {
    vec3 v;
    istream >> v;
    model.addVertex(std::move(v));
}
void parseVertexNormal(ObjParserModel &model, std::istream &istream) {
    vec3 v;
    istream >> v;
    model.addVertexNormal(std::move(v));
}
void parseVertexTexture(ObjParserModel &model, std::istream &istream) {
    vec2 v;
    istream >> v;
    model.addVertexTexture(std::move(v));
}
void parseFace(ObjParserModel &model, std::istream &istream) {
    ObjFace f;
    istream >> f;
    model.addFace(std::move(f));
}

typedef std::unordered_map<std::string, std::function<void(ObjParserModel&, std::istream&)>> ParsingTable;

void initMap(ParsingTable &_map) {
    _map["v"] = parseVertex;
    _map["vt"] = parseVertexTexture;
    _map["vn"] = parseVertexNormal;
    _map["f"] = parseFace;
}

static ParsingTable map() {
    static ParsingTable _map;
    if (_map.empty()) {
        initMap(_map);
    }
    return _map;
}

ObjParser::ObjParser() { }

ObjParserModel ObjParser::parse(std::istream &istream) {
    auto parserModel = ObjParserModel();
    auto m = map();

    std::string s;
    while(istream >> s) {
        if (m.count(s) > 0) {
            m[s](parserModel, istream);
        }
    }

    return parserModel;
}
