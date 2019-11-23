#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include <QGraphicsPathItem>
#include <QSet>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMessageBox>


class PuzzlePiece : public QGraphicsPathItem
{
public:
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(QPoint coordinates READ coordinates WRITE setCoordinates)

    enum ConnectorPosition {None, Out, In};
    enum Direction {North, East, South, West};
    PuzzlePiece(ConnectorPosition, ConnectorPosition, ConnectorPosition, ConnectorPosition, int);

    QPixmap pixmap();
    void setPixmap(QPixmap &);
    QPoint coordinates();
    void setCoordinates(QPoint);
    void link(PuzzlePiece*, Direction);
    void checkNeighbours(QSet<QPoint> &);
    void findneighbour(Direction direction);
    void setNumber(const QSize &);
    QVariant itemChange(GraphicsItemChange, const QVariant &);
private:
    int p_size;
    int number;
    QPixmap pix;
    ConnectorPosition sides[4];
    PuzzlePiece *m_neighbors[4];
    QPoint _coordinates;

    void constructShape(QPainterPath &);
    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget = nullptr);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};

#endif // PUZZLEPIECE_H
