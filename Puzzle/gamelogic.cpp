#include "gamelogic.h"


PuzzlePiece::ConnectorPosition GameLogic::reverse(PuzzlePiece::ConnectorPosition pos) {
    switch(pos){
        case PuzzlePiece::None: return PuzzlePiece::None;
        case PuzzlePiece::In: return PuzzlePiece::Out;
        case PuzzlePiece::Out: return PuzzlePiece::In;
    }
    return PuzzlePiece::None; // safeguard
}

void GameLogic::setup(const QSize &size, const QPixmap &pix){
    const int p_size = 100;
    PuzzlePiece::ConnectorPosition storedWest;
    QVector<PuzzlePiece::ConnectorPosition> prev(size.width(),
                                                 PuzzlePiece::None);
    for(int row = 0; row < size.height(); ++row) {
        storedWest = PuzzlePiece::None;
        for(int col = 0; col < size.width(); ++col) {
            PuzzlePiece::ConnectorPosition curr[4]; // N, E, S, W

            curr[0] = reverse(prev[col]);
            curr[1] = qrand() % 2 ? PuzzlePiece::In : PuzzlePiece::Out;
            curr[2] = qrand() % 2 ? PuzzlePiece::In : PuzzlePiece::Out;
            curr[3] = reverse(storedWest);
            if(col==size.width()-1) curr[1] = PuzzlePiece::None;
            if(row==size.height()-1) curr[2] = PuzzlePiece::None;

            PuzzlePiece *piece = new PuzzlePiece(curr[0], curr[1],
                                             curr[2], curr[3], p_size);
            piece->setCoordinates(QPoint(col, row));

            QRect rect = piece->boundingRect().toRect(); // (0,0) в центре
            rect.translate(0.5*p_size + col*p_size, 0.5*p_size + row*p_size);
            QPixmap px = pix.scaled(size.width() * p_size, size.height() * p_size, Qt::KeepAspectRatioByExpanding).copy(rect);
            piece->setPixmap(px);

            addItem(piece); // add item to scene
            piece->setFlag(QGraphicsItem::ItemIsMovable);
            piece->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
            double x_rand = size.width() * p_size * (double)qrand() / RAND_MAX;
            double y_rand = size.height() * p_size * (double)qrand() / RAND_MAX;
            piece->setPos(x_rand, y_rand); // put the piece in place
            piece->setNumber(size);

            storedWest = curr[1]; // store east for next column
            prev[col] = curr[2];  // store south for next row
        }
    }
}
