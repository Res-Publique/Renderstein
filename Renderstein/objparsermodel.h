#ifndef OBJPARSERMODEL_H
#define OBJPARSERMODEL_H


#include "objface.h"
#include "vec2.h"
#include "vec3.h"

#include <vector>

class ObjParserModel
{
public:
    ObjParserModel();
    void addVertex(vec3 &&v);
    void addVertexNormal(vec3 &&v);
    void addVertexTexture(vec2 &&v);
    void addFace(ObjFace &&face);
private:
    std::vector<vec3> verticies;
    std::vector<vec3> vertexNormals;
    std::vector<vec2> vertexTextures;
    std::vector<ObjFace> faces;
};

#endif // OBJPARSERMODEL_H
