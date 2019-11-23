#include "puzzlesizewidget.h"
#include <QVariant>
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>

PuzzleSizeWidget::PuzzleSizeWidget(QWidget *parent)
    : QFrame(parent)
{
    size = QSize(7, 4);
    min = QSize(2, 2);
    max = QSize(8, 8);
    pix = QPixmap();
}

QSize PuzzleSizeWidget::sizeHint() const{
    int cell_length = cellSize().width();
    return QSize(size.width() * cell_length, size.height() * cell_length);
}

QSize PuzzleSizeWidget::value() const{
    return size;
}

void PuzzleSizeWidget::setValue(const QSize &s){
    if (size == s) return;
    if (s.width() < minimum().width() || s.height() < minimum().height())
        return;
    if (s.width() > maximum().width() || s.height() > maximum().height())
        return;
    QSize old = size;
    size = s;
    emit valueChanged(s);
    if (old.width() != s.width())emit horizontalValueChanged(s.width());
    if (old.height() != s.height())emit verticalValueChanged(s.height());
    update();
}

void PuzzleSizeWidget::setMinimum(const QSize &m){
    if (size.width() < m.width() || size.height() < m.height())
        return;
    min = m;
}

QSize PuzzleSizeWidget::minimum() const{
    return min;
}

void PuzzleSizeWidget::setMaximum(const QSize &m){
    if (size.width() > m.width() || size.height() > m.height())
        return;
    max = m;
}

QSize PuzzleSizeWidget::maximum() const{
    return max;
}

void PuzzleSizeWidget::setPixmap(const QPixmap& p){
    pix = p;
}

QPixmap PuzzleSizeWidget::pixmap() const{
    return pix;
}

void PuzzleSizeWidget::paintEvent(QPaintEvent *event){
    int width = 1;
    QPen pen(QBrush(Qt::black), width, Qt::SolidLine);
    QPainter painter(this);
    painter.setPen(pen);
    renderValue(painter);
    renderGrid(painter);
}

QSize PuzzleSizeWidget::cellSize() const{
    int w = int(width() * 0.98);
    int h = int(height() * 0.98);
    int mw = maximum().width();
    int mh = maximum().height();
    int extent = qMin(w/mw, h/mh);
    return QSize(extent, extent);
}

void PuzzleSizeWidget::renderValue(QPainter& q){
    int cell_length = cellSize().width();
    if (!pix.isNull()){
        q.drawPixmap(QRect(0, 0, size.width() * cell_length, size.height() * cell_length),
                     pix.scaled(size.width() * cell_length, size.height() * cell_length, Qt::KeepAspectRatioByExpanding),
                     QRectF(0, 0, size.width() * cell_length, size.height() * cell_length));
    }
    else q.setBrush(Qt::gray);

    int x = 0, y = 0;
    for (int i = 0; i < size.width() * size.height(); i++){
        if (i % size.width() == 0 && i != 0){
            x = 0;
            y += cell_length;
        }
        q.drawRect(QRectF(QPointF(x, y), cellSize()));
        x += cell_length;
    }
}

void PuzzleSizeWidget::renderGrid(QPainter& q){
    q.setBrush(Qt::NoBrush);
    int cell_length = cellSize().width();
    int x, y = 0;
    for (int i = 0; i < size.height(); i++){
        for (int j = size.width(); j < max.width(); j++){
            x = j * cell_length;
            q.drawRect(QRectF(QPointF(x, y), cellSize()));
        }
        y += cell_length;
    }

    y = size.height() * cell_length;
    for (int i = size.height(); i < max.height(); i++){
        for (int j = 0; j < max.width(); j++){
            x = j * cell_length;
            q.drawRect(QRectF(QPointF(x, y), cellSize()));
        }
        y += cell_length;
    }
}

QSize PuzzleSizeWidget::cellAt(QPoint p){
    if (p.x() > width() || p.y() > height()) return QSize(-1, -1);
    int cell_length = cellSize().width();
    QSize result(p.x() / cell_length + 1, p.y() / cell_length + 1);
    if (result.width() > max.width() || result.height() > max.height()) return QSize(-1, -1);
    return result;
}

void PuzzleSizeWidget::mousePressEvent(QMouseEvent *event){
    setValue(cellAt(event->pos()));
}
void PuzzleSizeWidget::mouseMoveEvent(QMouseEvent *event){
    setValue(cellAt(event->pos()));
}
