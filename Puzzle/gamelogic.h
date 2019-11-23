#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QGraphicsScene>
#include <puzzlepiece.h>
#include <QDebug>
#include <cstdlib>

class GameLogic : public QGraphicsScene
{
public:
    PuzzlePiece::ConnectorPosition reverse(PuzzlePiece::ConnectorPosition);
    void setup(const QSize &, const QPixmap &);
signals:

public slots:
};

#endif // GAMELOGIC_H
