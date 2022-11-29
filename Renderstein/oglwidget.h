#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "objmodel.h"
#include "objparsermodel.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <GL/glu.h>

class OGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    void setModel(std::shared_ptr<ObjModel> model);
    void startTimer();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    std::shared_ptr<ObjModel> model = nullptr;

private:
    GLuint shaderProgram;
    GLuint vao, vbo, ebo;
    size_t eboSize;
};

#endif // OGLWIDGET_H
