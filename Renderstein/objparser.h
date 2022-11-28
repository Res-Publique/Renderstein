#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <objparsermodel.h>
#include <istream>

class ObjParser
{
public:
    ObjParser();
    ObjParserModel parse(std::istream &istream);
};

#endif // OBJPARSER_H
