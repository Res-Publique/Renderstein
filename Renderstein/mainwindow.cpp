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

    stack = new QStackedWidget(this);

    button = new QPushButton();
    connect(button, &QPushButton::released, this, &MainWindow::handleButton);

    oglwidget = new OGLWidget();

    stack->addWidget(button);
    stack->addWidget(oglwidget);

    QVBoxLayout *layout = new QVBoxLayout;
//    stack->setLayout(layout);
    stack->setFixedSize(this->frameSize());
    button->setFixedSize(this->frameSize());
    layout->addWidget(stack);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton() {
    stack->setCurrentIndex(1);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
    }

    if (fileNames.size() > 0) {
        auto file = fileNames[0].toStdString();
        std::ifstream stream;
        stream.open(file);
        stream.sync_with_stdio(false);
        auto parser = ObjParser();
        auto obj = std::make_shared<ObjParserModel>(parser.parse(stream));
        oglwidget->setModel(obj);
    }
}
