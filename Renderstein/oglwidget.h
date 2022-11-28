#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "objparsermodel.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <GL/gl.h>

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    void setModel(std::shared_ptr<ObjParserModel> model);
    void startTimer();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    std::shared_ptr<ObjParserModel> model = nullptr;
};

#endif // OGLWIDGET_H
