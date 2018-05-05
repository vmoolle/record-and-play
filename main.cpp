#include "recordandplay.h"
#include "recorder.h"
#include "player.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

const QString targetFileName = "record-and-play.wav";

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView w;

    QSize minSize(300, 200);
    w.setMinimumSize(minSize);
    w.resize(minSize);

    w.setResizeMode(QQuickView::SizeRootObjectToView);

    Recorder recorder;
    Player player;

    RecordAndPlay recordAndPlay(targetFileName, recorder, player);
    w.engine()->rootContext()->setContextProperty("recordAndPlay", &recordAndPlay);

    w.setSource(QUrl("qrc:/main.qml"));
    w.show();

    return app.exec();
}
