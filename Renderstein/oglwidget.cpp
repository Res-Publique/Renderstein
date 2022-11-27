#include "oglwidget.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QGLFormat>
#include <QTimer>
#include <iostream>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    model = nullptr;
    auto timer = new QTimer();
    timer->setInterval(30);
    connect(timer, &QTimer::timeout, this, [this]() {
        this->update();
    });
    timer->start(0);
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::setModel(std::shared_ptr<ObjParserModel> model)
{
    this->model = model;
}

void OGLWidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}


void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (model == nullptr) { return; }

    auto time = (float)QDateTime::currentDateTime().time().msecsSinceStartOfDay();

    auto t = sin(time / 1000.f);
    auto t2 = cos(time / 1000.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(t2,t,5,0,0,0,0,1,0);

    auto verticies = model->getVerticies();
    auto normals = model->getVertexNormals();
    auto faces = model->getFaces();
    auto generator = QRandomGenerator();
    generator.seed(time);
    for (auto &&face: faces) {
        if (face.v.size() <= 3) {
            glBegin(GL_TRIANGLES);
        } else if (face.v.size() == 4) {
            glBegin(GL_QUADS);
        } else {
            glBegin(GL_POLYGON);
        }
        for (auto i = 0; i < face.v.size(); i++) {
            auto vertex = verticies[face.v[i]];
            auto normal = normals[face.vn[i]];
            glVertex3f(vertex.x, vertex.y, vertex.z);
            auto r = normal.x;
            auto g = normal.y;
            auto b = normal.z;
//            auto r = generator.generateDouble();
//            auto g = generator.generateDouble();
//            auto b = generator.generateDouble();
            glColor3f(r, g, b);
        }
        glEnd();
    }
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
}
