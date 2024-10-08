//
// Created by pyy on 2024/8/13.
//

#ifndef LOG_H
#define LOG_H
#include <QFile>
#include <QMutex>

extern QString WhoRun;

class Logger
{
public:
    static Logger* instance();
    void logMessage(const QString &functionName, const QString &message, const QList<QString> &dataList = QList<QString>());
private:
    Logger();
    ~Logger();
    QFile logFile;
    QMutex mutex; // 用于线程安全的日志记录
    static Logger* instancePtr;
};
#endif //LOG_H
