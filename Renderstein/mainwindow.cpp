#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "objparser.h"

#include <QFileDialog>
#include <QVBoxLayout>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button = new QPushButton;
    connect(button, &QPushButton::released, this, &MainWindow::handleButton);
    button->setText("Open");
    button->setFixedSize(100, 100);

    oglwidget = new OGLWidget;

    stack = new QStackedWidget(this);
    stack->addWidget(button);
    stack->addWidget(oglwidget);
    stack->setFixedSize(this->frameSize());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton() {
    stack->setCurrentIndex(1);
    auto fileNames = QFileDialog::getOpenFileNames(this, "Select a file to open...", QDir::homePath());

    if (fileNames.size() > 0) {
        auto file = fileNames[0].toStdString();
        std::ifstream stream(file);
        stream.sync_with_stdio(false);
        auto parser = ObjParser();
        auto obj = std::make_shared<ObjParserModel>(parser.parse(stream));
        oglwidget->setModel(obj);
        oglwidget->startTimer();
    }
}
