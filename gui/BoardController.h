#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QVariantList>
#include <QTimer>

#include "../GeneticMain/AbstractPlayer.h"
#include "../GeneticMain/Match.h"

#include "Player1/Player1.h"
#include "Player2/Player2.h"

class BoardController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList gameBoard READ gameBoard NOTIFY boardChanged)

public:
    explicit BoardController(QObject *parent = 0);
    ~BoardController();
    QVariantList gameBoard();

    void initializeMatchAndPlayers();
    void progressMove();

public slots:
    void insertAtColumn(int column);
    void reset();

signals:
    void boardChanged();

private:
     int board[6][7];
     unsigned int turnNumber;
     int getPlayerFromTurnNumber();

     Match internalMatch;
     Player1* p1;
     Player2* p2;
     QTimer* timer;
};

#endif // BOARDCONTROLLER_H
