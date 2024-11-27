#pragma once
#include <QObject>
#include <qqml.h>

class Notificator : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

public:
    explicit Notificator(QObject *parent = nullptr);
    static Notificator *instance();

signals:
    void notify(QString message);

private:
};
