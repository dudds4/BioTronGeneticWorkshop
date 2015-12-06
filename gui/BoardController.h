#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QVariantList>

class BoardController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList gameBoard READ gameBoard NOTIFY boardChanged)

public:
    explicit BoardController(QObject *parent = 0);
    QVariantList gameBoard();

public slots:
    void insertAtColumn(int column);
    void reset();

signals:
    void boardChanged();

private:
     int board[6][7];
     unsigned int turnNumber;
     int getPlayerFromTurnNumber();
};

#endif // BOARDCONTROLLER_H
