//
// Created by 13633 on 24-10-8.
//

#include "core.h"
#include "var_global.h"
#include "log.h"
#include "ui_designer.h"

#include <QDebug>
#include <QTextCodec>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QThread>
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    PartLine = "========";
    // init();
    SetupSlot();
}

MainWindow::~MainWindow()
{
    delete ui; // 释放资源
};

int MainWindow::SetupSlot() {
    connect(ui->SendRequest_pushButton, &QPushButton::clicked, this, &MainWindow::Slot_SendRequest_pushButton);
    return 0;

}

void MainWindow::on_finished()
{
    // 获取响应码
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(statusCode == 200)
    {
        qDebug() << "Head Data as follow";
        // 输出响应头信息
        QList<QByteArray> responseHeaders = reply->rawHeaderList();
        foreach (const QByteArray &header, responseHeaders)
        {
            qDebug() << header + " : " + reply->rawHeader(header);
        }
    }
}

// 读入页面源代码
void MainWindow::on_readyRead()
{
    QString OneText;
    QString Source;
    qDebug() << "All Data as follow";
    QByteArray content = reply->readAll();
    QString decode;
    qDebug() << "RAW Data is: " + content;
    if (ui->RequestReturnEncode_comboBox->currentIndex() == 0) {
        QTextCodec *encode = QTextCodec::codecForName("UTF-8");
        decode = encode->toUnicode(content);
    } else if (ui->RequestReturnEncode_comboBox->currentIndex() == 1) {
        QTextCodec *encode = QTextCodec::codecForName("GBK");
        decode = encode->toUnicode(content);
    }
    if(ui->RequestReturnType_comboBox->currentText() == "json") {
        qDebug() << "We should analyse response, cause u take json to receive!";
        QJsonDocument raw_response = QJsonDocument::fromJson(decode.toUtf8());
        qDebug() << raw_response;
        QJsonObject raw_response_ojb = raw_response.object();
        qDebug() << "id is: " << raw_response_ojb.value("id");
        qDebug() << "uuid is: " << raw_response_ojb.value("uuid");
        qDebug() << "hitokoto is: " << raw_response_ojb.value("hitokoto");
        qDebug() << "from is: " << raw_response_ojb.value("from");
        qDebug() << "from_who is: " << raw_response_ojb.value("from_who");
        OneText = raw_response_ojb.value("hitokoto").toString();
        Source = raw_response_ojb.value("from").toString();
    }
    ui->Display_HaveReceived->insertPlainText(decode + "\n");

    ui->Display_Screen->clear();
    QString OneText_Show = QString("<div align=\"center\">%1</div><div align=\"right\">%2</div>")
                        .arg(OneText)
                        .arg("————" + Source);
    ui->Display_Screen->setText(OneText_Show);
    // 设置垂直居中
    ui->Display_Screen->document()->setDefaultStyleSheet(
        "body { display: flex; align-items: center; height: 100%; }"
    );
}


void MainWindow::Slot_SendRequest_pushButton() {
    // collect information
    QString RequestUrl;
    QString RequestType;
    QString RequestReturnType;
    QString RequestReturnEncode;
    RequestUrl = ui->RequestUrl_comboBox->currentText();
    switch (ui->RequestType_comboBox->currentIndex()) {
        case 0:
            RequestType = "a";
            break;
        case 1:
            RequestType = "b";
            break;
        case 2:
            RequestType = "c";
            break;
        case 3:
            RequestType = "d";
            break;
        case 4:
            RequestType = "e";
            break;
        case 5:
            RequestType = "f";
            break;
        case 6:
            RequestType = "g";
            break;
        case 7:
            RequestType = "h";
            break;
        case 8:
            RequestType = "i";
            break;
        case 9:
            RequestType = "j";
            break;
        case 10:
            RequestType = "k";
            break;
        case 11:
            RequestType = "l";
            break;
        default:
            RequestType = "a";
            break;
    }

    RequestReturnType = ui->RequestReturnType_comboBox->currentText();

    RequestReturnEncode = ui->RequestReturnEncode_comboBox->currentText();

    qDebug() << PartLine + "Collect Information: Start" + PartLine;
    qDebug() << "Parameter: RequestUrl: " + RequestUrl;
    qDebug() << "Parameter: RequestType: " + RequestType;
    qDebug() << "Parameter: RequestReturnType: " + RequestReturnType;
    qDebug() << "Parameter: RequestReturnEncode: " + RequestReturnEncode;
    qDebug() << PartLine + "Collect Information: End" + PartLine;

    // 创建网络访问管理器
    QNetworkAccessManager NetManager;

    QString Url = "https://" + RequestUrl + "/?c=" + RequestType + "&encode=" + RequestReturnType + "&&charset=" + RequestReturnEncode;

    qDebug() << "We request url is: " + Url;

    reply = networkManager.get(QNetworkRequest(Url));

    // 完成时的槽函数绑定
    connect(reply, SIGNAL(finished()), this, SLOT(on_finished()));

    // 读入数据的槽函数绑定
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));



}