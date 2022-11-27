#include "objparsermodel.h"

ObjParserModel::ObjParserModel() {

}

ObjParserModel::ObjParserModel(ObjParserModel &&model)
{
    std::swap(verticies, model.verticies);
    std::swap(vertexNormals, model.vertexNormals);
    std::swap(vertexTextures, model.vertexTextures);
    std::swap(faces, model.faces);
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

std::vector<vec3> ObjParserModel::getVerticies()
{
    return verticies;
}

std::vector<vec3> ObjParserModel::getVertexNormals()
{
    return vertexNormals;
}

std::vector<vec2> ObjParserModel::getVertexTextures()
{
    return vertexTextures;
}

std::vector<ObjFace> ObjParserModel::getFaces()
{
    return faces;
}
