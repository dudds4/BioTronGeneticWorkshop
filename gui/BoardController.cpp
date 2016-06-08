#include "BoardController.h"
#include <QDebug>

BoardController::BoardController(QObject *parent) : QObject(parent)
{
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++)
            board[i][j] = 0;
    }
    turnNumber = 0;
    initializeMatchAndPlayers();
    timer = new QTimer();
    timer->setInterval(200);
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &BoardController::progressMove);
    timer->start();
}
BoardController::~BoardController() {
    if(p1) delete p1;
    if(p2) delete p2;

    p1 = NULL;
    p2 = NULL;

    delete timer;
    timer = NULL;
}

QVariantList BoardController::gameBoard() {
   //qDebug() << "gettingBoard for qml";
    QList<QVariant> result;
    internalMatch.copyBoardOut(board, 3);

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++)
            result.append(board[i][j]);
    }
    return result;
}

void BoardController::initializeMatchAndPlayers() {
    p1 = Player1::fromFile("p1File.txt");
    p2 = Player2::fromFile("p2File.txt");

    internalMatch.setPlayer1(p1);
    internalMatch.setPlayer2(p2);
}

void BoardController::progressMove() {
    bool done = internalMatch.playNextMove();
    emit boardChanged();
    if(done) {
        timer->stop();
        qDebug() << "Game Over";
    }
}

void BoardController::reset() {
    qDebug() << "Not really relevant";
    return;

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++)
            board[i][j] = 0;
    }
    emit boardChanged();
}

int BoardController::getPlayerFromTurnNumber() {
    return ((turnNumber % 2) + 1);
}

void BoardController::insertAtColumn(int column) {
    //qDebug() << "Made into BoardController::insertAtColumn";
    if(column > 6 || column < 0) return;    //column is out of range
    if(board[0][column] > 0) return;        //column is already full

    int row = 0;
    while(row + 1 < 6 && board[row + 1][column] == 0)
        row++;

    int playerNumber = getPlayerFromTurnNumber();
    board[row][column] = playerNumber;
    //qDebug() << "Set row: " << row << "column: " << column << "to player: " << playerNumber;
    turnNumber++;
    emit boardChanged();
}
