#include "Translator.hpp"

#include <QTranslator>
#include <QCoreApplication>

#include "Settings.hpp"

namespace translator
{
    void install(QCoreApplication &app)
    {
        QTranslator translator;
        QString language = Settings::instance()->getValue("Language").toString();
        if (translator.load(QString(":/translations/%1.qm").arg(language)))
        {
            app.installTranslator(&translator);
            qDebug() << language << " translation loaded.";
        }
        else
        {
            qCritical("Invalid language setting, English translation loaded by default.");
            if (translator.load(":/translations/English"))
                app.installTranslator(&translator);
        }
    }
}