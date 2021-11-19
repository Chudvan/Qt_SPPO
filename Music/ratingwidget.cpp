#include "ratingwidget.h"
#include <QDebug>

RatingWidget::RatingWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void RatingWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QBrush colorized(Qt::green);
    QBrush nocolor(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 1));
    int top = 0, left = 0;
    for (int i = 0; i < 5; i++){
        if (_rating > 0 && i < _rating)painter.setBrush(colorized);
        else painter.setBrush(nocolor);
        painter.drawEllipse(QPoint(left + 9, top + 9), 8, 8);
        left += 20;
    }
}

void RatingWidget::mouseReleaseEvent(QMouseEvent *event){
    emit editingCompleted();
}

void RatingWidget::mouseMoveEvent(QMouseEvent *event){
    setRating(roundingRating(event->x()));
    update();
}

int RatingWidget::roundingRating(int position){
    return position / (100 / 5) + 1;
}
