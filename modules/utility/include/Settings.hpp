#pragma once
#include <QObject>
#include <qqml.h>
#include <QSettings>

#include <mutex>

class Settings : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

public:
    explicit Settings();
    static Settings *instance();
    Q_INVOKABLE QVariant getValue(const QString &key) const;
    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);
    Q_INVOKABLE bool contains(const QString &key) const;

signals:
    void settingUpdated(const QString &key, const QVariant &value);

private:
    QSettings m_settings;
    mutable std::mutex m_mutex;
};
