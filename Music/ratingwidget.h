#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <item.h>
#include <QPainter>

class RatingWidget : public QWidget
{
    Q_OBJECT
    int _rating;
public:
    explicit RatingWidget(QWidget *parent = nullptr);
    int rating()const { return _rating; }
    void setRating(int _r) { _rating = _r; }
    QSize sizeHint () const{ return QSize(98, 18); }
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int roundingRating(int position);
signals:
    void editingCompleted();
public slots:
};

#endif // RATINGWIDGET_H
