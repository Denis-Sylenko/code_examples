#include "mymodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileDialog>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MyModel modelData(&app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(&modelData));
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
