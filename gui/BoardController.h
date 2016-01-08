#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QVariantList>
#include <QTimer>

#include "../GeneticMain/AbstractPlayer.h"
#include "../GeneticMain/Player.h"
#include "../GeneticMain/Match.h"

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
     Player* p1;
     Player* p2;
     QTimer* timer;
};

#endif // BOARDCONTROLLER_H
