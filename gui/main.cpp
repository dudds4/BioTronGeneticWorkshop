#include <QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QQmlApplicationEngine>
#include "BoardController.h"

static QObject* boardController_singletonTypeProvider(QQmlEngine* engine, QJSEngine* jsEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(jsEngine)
    BoardController* boardController = new BoardController();
    return boardController;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<BoardController>("com.biotron.boardcontroller", 1, 0, "BoardController", boardController_singletonTypeProvider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

