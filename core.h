//
// Created by 13633 on 24-10-08.
// A patch for guiCore.h
//

#pragma once

//系统标识符
#ifdef _WIN32
#define SYS 1
#elif __linux__
#define SYS 2
#elif __APPLE__
#define SYS 3
#endif

#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QTableWidget>
#include <QTimer>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;


signals:


public slots:



private:
	Ui::MainWindow* ui;
};