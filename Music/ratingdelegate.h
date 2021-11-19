#ifndef RATINGDELEGATE_H
#define RATINGDELEGATE_H
#include <QStyledItemDelegate>
#include <item.h>
#include <QPainter>
#include "ratingwidget.h"


class RatingDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    RatingDelegate();
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
public slots:
    void commitChanges();
};

#endif // RATINGDELEGATE_H
