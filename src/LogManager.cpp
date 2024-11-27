#include "LogManager.hpp"

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <mutex>

namespace
{
    QString getApplicationPath()
    {
        auto dirPath = QCoreApplication::applicationDirPath();
        int appIndex = dirPath.indexOf(".app");
        if (appIndex != -1)
        { // macOs will return a path within the bundled .app
            int endIndex = dirPath.lastIndexOf('/', appIndex);
            dirPath = dirPath.left(endIndex);
        }
        return dirPath;
    }

    QFileInfo getLogFile()
    {
        static QFileInfo fileInfo;
        if (fileInfo.filePath().isEmpty())
        {
            const QString FILE_NAME = QDateTime::currentDateTime().toString("h_mmAP_yyyy_MM_dd") + ".log";
            static QDir logDir;
            if (logDir == QDir())
            {
                logDir = QDir(getApplicationPath() + "/logs");
                logDir.mkpath(".");
            }
            fileInfo = QFileInfo(logDir, FILE_NAME);
        }
        return fileInfo;
    }

    void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        static QFile logFile(getLogFile().absoluteFilePath());
        if (!logFile.isOpen())
        {
            logFile.open(QIODevice::Append | QIODevice::Text);
        }
        QTextStream out(&logFile);

        // use qSetMessagePattern to format
        auto message = qFormatLogMessage(type, context, msg);

        out << message << "\n";
        std::cerr << message.toStdString() << std::endl;

        out.flush();

        if (type == QtFatalMsg)
            abort();
    }

} // namespace

LogManager &LogManager::instance()
{
    static std::once_flag initFlag;
    static std::shared_ptr<LogManager> instancePtr;
    std::call_once(initFlag, []()
                   { instancePtr.reset(new LogManager());
                   instancePtr->init(); });
    return *instancePtr;
}

LogManager::~LogManager()
{
    qInstallMessageHandler(m_originalHandler);
}

void LogManager::init()
{
#ifdef QT_DEBUG
    qSetMessagePattern(
        "[%{time yyyy-MM-dd HH:mm:ss.zzz}] "
        "[%{if-debug}debug%{endif}%{if-info}info%{endif}%{if-warning}warning%{endif}%{if-critical}"
        "error%{endif}%{if-fatal}fatal%{endif}] %{file}:%{line}<%{function}>: %{message}");
#else
    qSetMessagePattern(
        "[%{time HH:mm:ss.zzz}] "
        "[%{if-debug}debug%{endif}%{if-info}info%{endif}%{if-warning}warning%{endif}%{if-critical}"
        "error%{endif}%{if-fatal}fatal%{endif}]: %{message}");
#endif
    m_originalHandler = qInstallMessageHandler(logHandler);
}