#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "objparsermodel.h"
#include "triangle.h"

class ObjModel
{
public:
    ObjModel(const ObjParserModel &model);

    const std::vector<vec3>& getVerticies() const;
    const std::vector<vec3>& getVertexNormals() const;
    const std::vector<vec2>& getVertexTextures() const;
    const std::vector<ObjFace>& getFaces() const;
    const std::vector<Triangle>& getTriangles() const;
private:
    std::vector<vec3> verticies;
    std::vector<vec3> vertexNormals;
    std::vector<vec2> vertexTextures;
    std::vector<ObjFace> faces;
    std::vector<Triangle> triangles;
};

#endif // OBJMODEL_H
