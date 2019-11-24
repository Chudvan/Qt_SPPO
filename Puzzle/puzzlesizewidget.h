#ifndef PUZZLESIZEWIDGET_H
#define PUZZLESIZEWIDGET_H

#include <QFrame>

class PuzzleSizeWidget : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QSize value READ value WRITE setValue)
    Q_PROPERTY(QSize minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(QSize maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
public:
    explicit PuzzleSizeWidget(QWidget *parent = 0);
    QSize sizeHint() const override;
    QSize value() const;
    QSize minimum() const;
    QSize maximum() const;
    QPixmap pixmap() const;

public slots:
    void setValue(const QSize &);
    void setMinimum(const QSize &);
    void setMaximum(const QSize &);
    void setPixmap(const QPixmap&);
signals:
    void valueChanged(const QSize &);
    void horizontalValueChanged(int);
    void verticalValueChanged(int);
protected:
    void paintEvent(QPaintEvent *) override;
private:
    QSize min, max, size;
    QPixmap pix;
    QSize cellSize() const;

    void renderValue(QPainter&);
    void renderGrid(QPainter&);
    QSize cellAt(QPoint);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // PUZZLESIZEWIDGET_H
