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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QTableWidget>
#include <QTimer>

extern QString PartLine;

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

	QTimer *simmulation = new QTimer(this);
	int SetupSlot();
	void Slot_SendRequest_pushButton();
	void slot_IsSimulation();
	void simmulation_timeout();
	void emitInfoStatus(const QString &msg);


signals:


public slots:
	void on_finished();
	void on_readyRead();
	void InitialDataBase();
	bool SaveToDataBase(const QString &uuid, const QString &type ,const QString &hitokoto, const QString &source, const QString &from_who);
	void fetchRandomHitokotoFromDatabase();
	QString TypeTranslate(const int index);


private:
	Ui::MainWindow* ui;
	QNetworkAccessManager networkManager;   // 网络管理
	QNetworkReply *reply;                   // 网络响应
};