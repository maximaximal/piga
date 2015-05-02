#include <iostream>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QtQuick/QQuickWindow>
#include <QQmlContext>
#include <QtQml>
#include <Client.hpp>
#include <ClientManager.hpp>

#include <../../include/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ClientManager mgr;
    QQmlApplicationEngine engine;

    qmlRegisterType<Client>("com.pigaco.networking", 1, 0, "Client");
    engine.rootContext()->setContextProperty("clientMgr", &mgr);
    engine.addImportPath("forms/");

    engine.load(QUrl::fromLocalFile("forms/MainView.qml"));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow*>(topLevel);

    window->show();

    app.exec();
}
