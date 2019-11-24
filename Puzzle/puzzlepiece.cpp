#include "puzzlepiece.h"

PuzzlePiece::PuzzlePiece(ConnectorPosition north, ConnectorPosition east,
                         ConnectorPosition south, ConnectorPosition west, int psize){
    sides[0] = north;
    sides[1] = east;
    sides[2] = south;
    sides[3] = west;

    p_size = psize;

    for (int i = 0; i < 4; i++)m_neighbors[i] = nullptr;

    QPainterPath pp;
    constructShape(pp);
    setPath(pp);
}

void PuzzlePiece::constructShape(QPainterPath &pp){
    pp.moveTo(-p_size / 2, -p_size / 2);
    switch(sides[0]){
        case None:
           pp.lineTo(p_size / 2, -p_size / 2);
           break;
        case Out:
            pp.lineTo(-p_size / 16, -p_size / 2);
            pp.arcTo(-p_size / 8, -p_size / 2 -p_size / 8,
                     p_size / 8, p_size / 8, 270, -90.0);
            pp.arcTo(-p_size / 8, -p_size / 2 -p_size / 8 -p_size / 16,
                     p_size / 4, p_size / 4, 180, -180.0);
            pp.arcTo(0, -p_size / 2 -p_size / 8,
                     p_size / 8, p_size / 8, 0, -90.0);
            pp.lineTo(p_size / 2, -p_size / 2);
            break;
        case In:
            pp.lineTo(-p_size / 16, -p_size / 2);
            pp.arcTo(-p_size / 8, -p_size / 2,
                     p_size / 8, p_size / 8, 90, 90.0);
            pp.arcTo(-p_size / 8, -p_size / 2 -p_size / 16,
                     p_size / 4, p_size / 4, 180, 180.0);
            pp.arcTo(0, -p_size / 2,
                     p_size / 8, p_size / 8, 0, 90.0);
            pp.lineTo(p_size / 2, -p_size / 2);
            break;
    }
    switch(sides[1]){
        case None:
           pp.lineTo(p_size / 2, p_size / 2);
           break;
        case Out:
            pp.lineTo(p_size / 2 , -p_size / 16);
            pp.arcTo(p_size / 2, -p_size / 8,
                     p_size / 8, p_size / 8, 180, -90.0);
            pp.arcTo(p_size / 2 -p_size / 16, -p_size / 8,
                     p_size / 4, p_size / 4, 90, -180.0);
            pp.arcTo(p_size / 2, 0,
                     p_size / 8, p_size / 8, 270, -90.0);
            pp.lineTo(p_size / 2, p_size / 2);
            break;
        case In:
            pp.lineTo(p_size / 2 , -p_size / 16);
            pp.arcTo(p_size / 2 -p_size / 8, -p_size / 8,
                     p_size / 8, p_size / 8, 0, 90.0);
            pp.arcTo(p_size / 2 -p_size / 8 -p_size / 16, -p_size / 8,
                     p_size / 4, p_size / 4, 90, 180.0);
            pp.arcTo(p_size / 2 -p_size / 8, 0,
                     p_size / 8, p_size / 8, 270, 90.0);
            pp.lineTo(p_size / 2, p_size / 2);
            break;
    }
    switch(sides[2]){
        case None:
           pp.lineTo(-p_size / 2, p_size / 2);
           break;
        case Out:
            pp.lineTo(p_size / 16, p_size / 2);
            pp.arcTo(0, p_size / 2,
                     p_size / 8, p_size / 8, 90, -90.0);
            pp.arcTo(-p_size / 8, p_size / 2 -p_size / 16,
                     p_size / 4, p_size / 4, 0, -180.0);
            pp.arcTo(-p_size / 8, p_size / 2,
                     p_size / 8, p_size / 8, 180, -90.0);
            pp.lineTo(-p_size / 2, p_size / 2);
            break;
        case In:
            pp.lineTo(p_size / 16, p_size / 2);
            pp.arcTo(0, p_size / 2 -p_size / 8,
                     p_size / 8, p_size / 8, 270, 90.0);
            pp.arcTo(-p_size / 8, p_size / 2 -p_size / 8 -p_size / 16,
                     p_size / 4, p_size / 4, 0, 180.0);
            pp.arcTo(-p_size / 8, p_size / 2 -p_size / 8,
                     p_size / 8, p_size / 8, 180, 90.0);
            pp.lineTo(-p_size / 2, p_size / 2);
            break;
    }
    switch(sides[3]){
        case None:
           pp.lineTo(-p_size / 2, -p_size / 2);
           break;
        case Out:
            pp.lineTo(-p_size / 2 , p_size / 16);
            pp.arcTo(-p_size / 2 -p_size / 8, 0,
                     p_size / 8, p_size / 8, 0, -90.0);
            pp.arcTo(-p_size / 2 -p_size / 8 -p_size / 16, -p_size / 8,
                     p_size / 4, p_size / 4, 270, -180.0);
            pp.arcTo(-p_size / 2 -p_size / 8, -p_size / 8,
                     p_size / 8, p_size / 8, 90, -90.0);
            pp.lineTo(-p_size / 2, -p_size / 2);
            break;
        case In:
            pp.lineTo(-p_size / 2 , p_size / 16);
            pp.arcTo(-p_size / 2, 0,
                     p_size / 8, p_size / 8, 180, 90.0);
            pp.arcTo(-p_size / 2 -p_size / 16, -p_size / 8,
                     p_size / 4, p_size / 4, 270, 180.0);
            pp.arcTo(-p_size / 2, -p_size / 8,
                     p_size / 8, p_size / 8, 90, 90);
            pp.lineTo(-p_size / 2, -p_size / 2);
            break;
    }
    pp.closeSubpath();
}

QPixmap PuzzlePiece::pixmap(){
    return pix;
}

void PuzzlePiece::setPixmap(QPixmap &p){
    pix = p;
    update();
}

void PuzzlePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black, 1));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(path());
    painter->setClipPath(path());
    QRect rect = boundingRect().toRect();
    painter->drawPixmap(rect.x(), rect.y(), pixmap());
}

QPoint PuzzlePiece::coordinates(){
    return _coordinates;
}
void PuzzlePiece::setCoordinates(QPoint p){
    _coordinates = p;
}

void PuzzlePiece::link(PuzzlePiece* ppiece, Direction direction){
    m_neighbors[direction] = ppiece;
    switch(direction){
        case North:
            ppiece->m_neighbors[South] = this;
            break;
        case East:
            ppiece->m_neighbors[West] = this;
            break;
        case South:
            ppiece->m_neighbors[North] = this;
            break;
        case West:
            ppiece->m_neighbors[East] = this;
            break;
    }
}

void PuzzlePiece::checkNeighbours(QSet<QPoint> &checked){
    if(checked.contains(coordinates()))
        return; // условия прерывания рекурсии
    checked.insert(coordinates()); // запомнить посещенный элемент
    findneighbour(North);     	// найти N соседа
    findneighbour(East);      	// найти E соседа
    findneighbour(South);     	// найти S соседа
    findneighbour(West);      	// найти W соседа

    // рекурсивные вызовы:
    if(m_neighbors[North])
        m_neighbors[North]->checkNeighbours(checked);
    if(m_neighbors[East])
        m_neighbors[East]->checkNeighbours(checked);
    if(m_neighbors[South])
        m_neighbors[South]->checkNeighbours(checked);
    if(m_neighbors[West])
        m_neighbors[West]->checkNeighbours(checked);
}

void PuzzlePiece::findneighbour(Direction direction){
    if (m_neighbors[direction]) return;
    PuzzlePiece* element;
    switch(direction){
        case North:
            element = (PuzzlePiece*)scene()->itemAt(pos().x(), pos().y() - p_size, QTransform());
            if (element &&
                    (coordinates() - QPoint(0, 1)) == element->coordinates() &&
                    abs(pos().x() - element->pos().x()) < 10 &&
                    abs(pos().y() - p_size - element->pos().y()) < 10){
                link(element, North);
                element->setPos(pos().x(), pos().y() - p_size);
            }
            break;
        case East:
            element = (PuzzlePiece*)scene()->itemAt(pos().x() + p_size, pos().y(), QTransform());
            if (element &&
                    (coordinates() + QPoint(1, 0)) == element->coordinates() &&
                    abs(pos().x() + p_size - element->pos().x()) < 10 &&
                    abs(pos().y() - element->pos().y()) < 10){
                link(element, East);
                element->setPos(pos().x() + p_size, pos().y());
            }
            break;
        case South:
            element = (PuzzlePiece*)scene()->itemAt(pos().x(), pos().y() + p_size, QTransform());
            if (element &&
                    (coordinates() + QPoint(0, 1)) == element->coordinates() &&
                    abs(pos().x() - element->pos().x()) < 10 &&
                    abs(pos().y() + p_size - element->pos().y()) < 10){
                link(element, South);
                element->setPos(pos().x(), pos().y() + p_size);
            }
            break;
        case West:
            element = (PuzzlePiece*)scene()->itemAt(pos().x() - p_size, pos().y(), QTransform());
            if (element &&
                    (coordinates() - QPoint(1, 0)) == element->coordinates() &&
                    abs(pos().x() - p_size - element->pos().x()) < 10 &&
                    abs(pos().y() - element->pos().y()) < 10){
                link(element, West);
                element->setPos(pos().x() - p_size, pos().y());
            }
            break;
    }
}

void PuzzlePiece::setNumber(const QSize &s){
    number = s.width() * s.height();
}

void PuzzlePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QSet<QPoint> set;
    checkNeighbours(set);
    if (set.count() == number) QMessageBox::information(0, QString("Поздравляем!"), QString("Вы победили!"));
    QGraphicsPathItem::mouseReleaseEvent(event);
}

QVariant PuzzlePiece::itemChange(GraphicsItemChange change, const QVariant &value){
    QPoint newPos = value.toPoint();
    if(change == ItemPositionHasChanged){
        if (m_neighbors[North])
            m_neighbors[North]->setPos(newPos.x(), newPos.y() - p_size);
        if (m_neighbors[East])
            m_neighbors[East]->setPos(newPos.x() + p_size, newPos.y());
        if (m_neighbors[South])
            m_neighbors[South]->setPos(newPos.x(), newPos.y() + p_size);
        if (m_neighbors[West])
            m_neighbors[West]->setPos(newPos.x() - p_size, newPos.y());
    }
    return QGraphicsItem::itemChange(change, value);
}

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}
