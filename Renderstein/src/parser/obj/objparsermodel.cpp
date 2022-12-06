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

const std::vector<vec3>& ObjParserModel::getVerticies() const
{
    return verticies;
}

const std::vector<vec3>& ObjParserModel::getVertexNormals() const
{
    return vertexNormals;
}

const std::vector<vec2>& ObjParserModel::getVertexTextures() const
{
    return vertexTextures;
}

const std::vector<ObjFace>& ObjParserModel::getFaces() const
{
    return faces;
}
