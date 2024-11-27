#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "SingletonGetter.hpp"
#include "Constants.hpp"
#include "LogManager.hpp"
#include "Translator.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    // log manager must be init after application is created
    LogManager::instance();
    QQmlApplicationEngine engine;
    Singleton::instance().initEngine(&engine);
    engine.addImportPath(":/qt/qml/");
    const QUrl url(QString("qrc:qt/qml/%1/qml/Main.qml").arg(constants::APPLICATION_NAME).replace(" ", ""));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
    translator::install(app); // needs the settings which is created from engine
    return app.exec();
}
