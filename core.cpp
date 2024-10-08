//
// Created by 13633 on 24-10-8.
//

#include "core.h"
#include "var_global.h"
#include "log.h"
#include "ui_designer.h"

#include <QDebug>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStatusBar>
#include <QThread>
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    // init();
}

MainWindow::~MainWindow()
{
    delete ui; // 释放资源
};