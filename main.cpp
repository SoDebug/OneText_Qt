#include "ui_designer.h"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include "version.h"
#include "log.h"
#include "main.h"
#include "core.h"


int main(int argc, char* argv[])
{
    bool is_auth = true;
    qDebug() << "CURRENT_VERSION_CODE is: " << CURRENT_VERSION_CODE;
    debug_flag = true;
    if (debug_flag)
    {
        WhoRun = __FUNCTION__;
        Logger::instance()->logMessage(WhoRun, QString("当前版本: ") + CURRENT_VERSION_CODE);
    }
    // // 定义试用截止时间，例如：2024年12月31日23:59:59
    // QDateTime trialEndTime = QDateTime::fromString("2024-10-16T23:59:59", Qt::ISODate);
    WhoRun = __FUNCTION__;
    Logger::instance()->logMessage(WhoRun, QString("Request approval for testing..."));

    // 获取当前系统时间
    QDateTime currentTime = QDateTime::currentDateTime();
    // 创建 QT 应用程序对象，初始化应用程序环境
    QApplication Core(argc, argv);
    // 如果当前时间小于试用截止时间，则退出程序

    if (is_auth != true) {
        QMessageBox::critical(nullptr, "体验结束(OS: " + QString(CURRENT_VERSION_CODE) + ")", "本阶段的测试已结束。\n感谢您的关注！");
        return 0; // 退出程序
    } else
    {
        QMessageBox::warning(nullptr, "体验提醒OS: " + QString(CURRENT_VERSION_CODE) + ")", "注意内部版本体验期之后无法继续体验。\n感谢您的关注！");
    }
    MainWindow UI; // 创建主窗口对象，代表用户界面
    UI.show();// 显示主窗口
    return QApplication::exec();
}
