#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQuick/QQuickWindow>

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine(QUrl::fromLocalFile("forms/MainView.qml"));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    app.exec();
}
