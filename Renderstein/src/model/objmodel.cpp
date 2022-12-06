#include "objmodel.h"

ObjModel::ObjModel(const ObjParserModel &model) {

    verticies = std::vector(model.getVerticies());
    vertexNormals = std::vector(model.getVertexNormals());
    vertexTextures = std::vector(model.getVertexTextures());
    faces = std::vector(model.getFaces());

    for (auto face: faces) {
        for (auto i = 2; i < face.v.size(); i++) {
            Triangle t;
            t.v0 = face.v[0];
            t.v1 = face.v[i - 1];
            t.v2 = face.v[i];
            triangles.push_back(t);
        }
    }
}

const std::vector<vec3> &ObjModel::getVerticies() const {
    return verticies;
}

const std::vector<vec3> &ObjModel::getVertexNormals() const {
    return vertexNormals;
}

const std::vector<vec2> &ObjModel::getVertexTextures() const {
    return vertexTextures;
}

const std::vector<ObjFace> &ObjModel::getFaces() const {
    return faces;
}

const std::vector<Triangle> &ObjModel::getTriangles() const {
    return triangles;
}
