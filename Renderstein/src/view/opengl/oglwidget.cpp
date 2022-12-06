#include "oglwidget.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QGLFormat>
#include <QTimer>
#include <iostream>
#include <QString>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

auto getVbo(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, vec3 shift) {
    std::vector<float> buffer;
    buffer.reserve(6 * vertices.size());

    for (size_t i = 0; i < vertices.size(); ++i) {
        buffer.push_back(vertices[i].x + shift.x);
        buffer.push_back(vertices[i].y + shift.y);
        buffer.push_back(vertices[i].z + shift.z);
        buffer.push_back(normals[i].x);
        buffer.push_back(normals[i].y);
        buffer.push_back(normals[i].z);
    }

    return buffer;
}

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    label = new QLabel(this);
    label->setStyleSheet("QLabel { background-color : red; color : blue; }");
    label->setFixedSize(QSize(50, 14));
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::setModel(std::shared_ptr<ObjModel> model)
{
    this->model = model;
    glGenBuffers(MONKEYS_COUNT, vbo);
    glGenBuffers(MONKEYS_COUNT, ebo);

    for (auto i = 0; i < MONKEYS_COUNT; i++) {
        vec3 shift;
        shift.x = 0;
        shift.y = i * 0.01f;
        shift.z = i * -0.1f;
        auto vboBuffer = getVbo(model->getVerticies(), model->getVertexNormals(), shift);

//        auto vboBuffer = getVbo(model->getVerticies(), model->getVertexNormals());
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        auto vboBufferSize = model->getVerticies().size() * 6 * sizeof(float);
        glBufferData(GL_ARRAY_BUFFER, vboBufferSize, vboBuffer.data(), GL_STATIC_DRAW);

        auto eboBuffer = model->getTriangles();
        eboSize[i] = eboBuffer.size() * 3;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize[i] * sizeof(GLuint), eboBuffer.data(), GL_STATIC_DRAW);
    }

    glGenVertexArrays(MONKEYS_COUNT, vao);
}

void OGLWidget::startTimer() {
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        this->update();
    });
    timer->start(0);
}

static const char *vertexShaderSource = "#version 420 core\n"
                                        "layout (location = 0) in vec3 pos;\n"
                                        "layout (location = 1) in vec3 color;\n"
                                        "out vec3 outColor;\n"
                                        "uniform mat4 projection;\n"
                                        "uniform mat4 view;\n"
                                        "void main() {\n"
                                        "    gl_Position = projection * view * vec4(pos, 1.0f);\n"
                                        "    outColor = color;\n"
                                        "}\0";

static const char *fragmentShaderSource = "#version 420 core\n"
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

    glUseProgram(shaderProgram);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)size().width()/size().height(), 0.01f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto time1 = (float)QDateTime::currentDateTime().time().msecsSinceStartOfDay();
    if (model == nullptr) { return; }

    auto time = (float)QDateTime::currentDateTime().time().msecsSinceStartOfDay();

    auto t = sin(time / 1000.f);
    auto t2 = cos(time / 1000.f);

    for (auto i = 0; i < MONKEYS_COUNT; i++) {
    glBindVertexArray(vao[i]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);
    glm::mat4 view = glm::lookAt(glm::vec3(t2, t, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"),
                       1, GL_FALSE, glm::value_ptr(view));

    glDrawElements(GL_TRIANGLES, eboSize[i], GL_UNSIGNED_INT, 0);
    }
    auto time2 = (float)QDateTime::currentDateTime().time().msecsSinceStartOfDay();
    auto dt = (int) round(time2 - time1);
    label->setText(QString::fromStdString(std::to_string(dt)));
}

void OGLWidget::resizeGL(int w, int h)
{
    glUseProgram(shaderProgram);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)w/h, 0.01f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"),
                       1, GL_FALSE, glm::value_ptr(view));
}
