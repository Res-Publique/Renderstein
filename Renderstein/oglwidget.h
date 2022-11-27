#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "ObjParserModel.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>

class OGLWidget : public QOpenGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    void setModel(std::shared_ptr<ObjParserModel> model);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    std::shared_ptr<ObjParserModel> model;
};

#endif // OGLWIDGET_H
