#include "log.h"

#include "core.h"

#include <QDateTime>
#include <QTextStream>

Logger* Logger::instancePtr = nullptr;
Logger* Logger::instance()
{
    if (!instancePtr) {
        instancePtr = new Logger();
        // set log path
        instancePtr->logFile.setFileName("app.log");
        instancePtr->logFile.open(QIODevice::Append | QIODevice::Text);
    }
    return instancePtr;
}
Logger::Logger()
{
    // 构造函数为空
}
Logger::~Logger()
{
    logFile.close();
}
void Logger::logMessage(const QString &functionName, const QString &message, const QList<QString> &dataList)
{
    QMutexLocker locker(&mutex); // 加锁确保线程安全
    QTextStream out(&logFile);
    if (dataList.isEmpty())
    {
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " " <<
        functionName << " report " << ":" << message << "\n";
    } else
    {
        QString cache;
        for (int i=0; i<dataList.size();i++)
        {
            cache = cache + ", " + dataList.at(i);
        }
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " " <<
        functionName << " report " << ":" << message << cache << "\n";
    }

    logFile.flush(); // 立即刷新到文件
}

