#ifndef OBJPARSERMODEL_H
#define OBJPARSERMODEL_H

#include "vec2generic.h"
#include "vec3generic.h"
#include "objface.h"
#include <vector>

class ObjParserModel
{
public:
    ObjParserModel();
    ObjParserModel(ObjParserModel &&model);
    void addVertex(vec3 &&v);
    void addVertexNormal(vec3 &&v);
    void addVertexTexture(vec2 &&v);
    void addFace(ObjFace &&face);

    const std::vector<vec3>& getVerticies() const;
    const std::vector<vec3>& getVertexNormals() const;
    const std::vector<vec2>& getVertexTextures() const;
    const std::vector<ObjFace>& getFaces() const;
private:
    std::vector<vec3> verticies;
    std::vector<vec3> vertexNormals;
    std::vector<vec2> vertexTextures;
    std::vector<ObjFace> faces;
};

#endif // OBJPARSERMODEL_H
