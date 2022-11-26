#include "objparsermodel.h"

ObjParserModel::ObjParserModel() {

}

void ObjParserModel::addVertex(vec3 &&v) {
    verticies.emplace_back(v);
}

void ObjParserModel::addVertexNormal(vec3 &&v) {
    vertexNormals.emplace_back(v);
}

void ObjParserModel::addVertexTexture(vec2 &&v) {
    vertexTextures.emplace_back(v);
}

void ObjParserModel::addFace(ObjFace &&face) {
    faces.emplace_back(face);
}
