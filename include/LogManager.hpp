#pragma once

#include <QObject>
#include <QtMessageHandler>

class LogManager : public QObject
{
    Q_OBJECT
public:
    static LogManager &instance();
    ~LogManager();

protected:
    LogManager() = default;

private:
    LogManager(const LogManager &) = delete;
    LogManager &operator=(const LogManager &) = delete;
    LogManager(LogManager &&) = delete;
    LogManager &operator=(LogManager &&) = delete;
    void init();

    QtMessageHandler m_originalHandler;
};