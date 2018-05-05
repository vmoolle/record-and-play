#include "recordandplay.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView w;

    QSize minSize(300, 200);
    w.setMinimumSize(minSize);
    w.resize(minSize);

    w.setResizeMode(QQuickView::SizeRootObjectToView);

    RecordAndPlay recordAndPlay;
    w.engine()->rootContext()->setContextProperty("recordAndPlay", &recordAndPlay);

    w.setSource(QUrl("qrc:/main.qml"));
    w.show();

    return app.exec();
}
