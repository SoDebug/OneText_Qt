#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建网络访问管理器
    QNetworkAccessManager manager;

    // 创建GET请求
    QNetworkRequest request(QUrl("http://www.baidu.com"));

    // 发送GET请求
    QNetworkReply *reply = manager.get(request);

    // 连接信号槽，处理响应
    QObject::connect(reply, &QNetworkReply::finished, [&]()
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            // 获取请求的 URL
            qDebug() << "Request URL:" << reply->request().url();

            // 输出请求头信息
            qDebug() << "Request Headers:";
            QList<QByteArray> requestHeaders = reply->request().rawHeaderList();
            foreach (const QByteArray &header, requestHeaders) {
                qDebug() << header << ":" << reply->request().rawHeader(header);
            }

            // 获取响应码
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << "HttpStatusCodeAttribute:" << statusCode;

            // 连接是否加密的标志
            bool connectionEncryptedAttribute = reply->attribute(QNetworkRequest::ConnectionEncryptedAttribute).toBool();
            qDebug() << "ConnectionEncryptedAttribute:" << connectionEncryptedAttribute;

            // 请求是否来自缓存的标志
            bool sourceIsFromCacheAttribute = reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool();
            qDebug() << "SourceIsFromCacheAttribute:" << sourceIsFromCacheAttribute;

            // HTTP请求是否被允许进行流水线处理的标志
            bool httpPipeliningAllowedAttribute = reply->attribute(QNetworkRequest::HttpPipeliningAllowedAttribute).toBool();
            qDebug() << "HttpPipeliningAllowedAttribute:" << httpPipeliningAllowedAttribute;

            // 输出响应头信息
            qDebug() << "Response Headers:";
            QList<QByteArray> responseHeaders = reply->rawHeaderList();
            foreach (const QByteArray &header, responseHeaders) {
                qDebug() << header << ":" << reply->rawHeader(header);
            }

            // 处理响应内容，这里可以使用 readAll() 方法获取响应内容
            // qDebug() << "Response Content:" << reply->readAll();
        } else
        {
            qDebug() << "Error:" << reply->errorString();
        }

        // 释放资源
        reply->deleteLater();
        QCoreApplication::quit();
    });

    return a.exec();
}
