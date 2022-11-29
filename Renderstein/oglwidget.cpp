#include "oglwidget.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QGLFormat>
#include <QTimer>
#include <iostream>

auto getVbo(const std::vector<vec3>& vertices, const std::vector<vec3>& normals) {
    float *buffer = new float[vertices.size() * 6];

    for (size_t i = 0; i < vertices.size(); ++i) {
        auto base = i * 6;
        memcpy(&buffer[base], &vertices[i], sizeof(float) * 3);
        memcpy(&buffer[base + 3], &normals[i], sizeof(float) * 3);
    }

    return buffer;
}

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::setModel(std::shared_ptr<ObjModel> model)
{
    this->model = model;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    auto vboBuffer = getVbo(model->getVerticies(), model->getVertexNormals());
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    auto vboBufferSize = model->getVerticies().size() * 6 * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, vboBufferSize, vboBuffer, GL_STATIC_DRAW);

    auto eboBuffer = model->getTriangles();
    eboSize = eboBuffer.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize * sizeof(GLuint), eboBuffer.data(), GL_STATIC_DRAW);
    delete[] vboBuffer;
}

void OGLWidget::startTimer() {
    auto timer = new QTimer(this);
    timer->setInterval(30);
    connect(timer, &QTimer::timeout, this, [this]() {
        this->update();
    });
    timer->start(0);
}

static const char* vertexShaderSource = "#version 420 core\n"
                                        "layout (location = 0) in vec3 pos;\n"
                                        "layout (location = 1) in vec3 color;\n"
                                        "out vec3 outColor;\n"
                                        "void main() {\n"
                                        "    gl_Position = vec4(pos, 1.0);\n"
                                        "    outColor = color + vec3(pos.y * 0.5);\n"
                                        "}\0";

static const char* fragmentShaderSource = "#version 420 core\n"
                                          "out vec4 fragColor;\n"
                                          "in vec3 outColor;\n"
                                          "void main() {\n"
                                          "    fragColor = vec4(outColor * vec3(1., 0., 0.), 1.0f);\n"
                                          "}\0";

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "vertexShader compilation error";
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "fragmentShader compilation error";
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        std::cout << "shaderProgram linking error";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, eboSize, GL_UNSIGNED_INT, 0);

    /*auto verticies = model->getVerticies();
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
        for (int i = face.v.size() - 1; i >= 0; i--) {
            auto vertex = verticies[face.v[i] - 1];
            //auto normal = normals[face.vn[i] - 1];
            glVertex3f(vertex.x, vertex.y, vertex.z);
            auto r = normal.x;
            auto g = normal.y;
            auto b = normal.z;
            glColor3f(r, g, b);
        }
        glEnd();
    }*/
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
