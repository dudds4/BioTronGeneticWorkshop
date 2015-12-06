#include "BoardController.h"
#include <QDebug>

BoardController::BoardController(QObject *parent) : QObject(parent)
{
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++)
            board[i][j] = 0;
    }
    turnNumber = 0;
}


QVariantList BoardController::gameBoard() {
   //qDebug() << "gettingBoard for qml";
    QList<QVariant> result;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++)
            result.append(board[i][j]);
    }
    return result;
}

void BoardController::reset() {
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
