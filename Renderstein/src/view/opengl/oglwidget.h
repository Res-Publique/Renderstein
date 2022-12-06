#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "objmodel.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QLabel>
#include <GL/glu.h>

#define MONKEYS_COUNT 10

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
    QLabel *label;
    GLuint shaderProgram;
    GLuint vao[MONKEYS_COUNT], vbo[MONKEYS_COUNT], ebo[MONKEYS_COUNT];
    size_t eboSize[MONKEYS_COUNT];
    float t;
};

#endif // OGLWIDGET_H
