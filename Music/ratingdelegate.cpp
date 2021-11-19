#include "ratingdelegate.h"
#include <QDebug>

RatingDelegate::RatingDelegate()
{

}

QSize RatingDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const{
    return QSize(98, 18);
}

void RatingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    Item *item = static_cast<Item *>(index.internalPointer());
    if (!item->toSong()) return QStyledItemDelegate::paint(painter, option, index);
    QBrush colorized(Qt::yellow);
    QBrush nocolor(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 1));
    int top = option.rect.top(), left = option.rect.left();
    int rating = item->toSong()->rating();
    for (int i = 0; i < 5; i++){
        if (rating > 0 && i < rating)painter->setBrush(colorized);
        else painter->setBrush(nocolor);
        painter->drawEllipse(QPoint(left + 9, top + 9), 8, 8);
        left += 20;
    }
}

QWidget *RatingDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    Item *item = static_cast<Item *>(index.internalPointer());
    if (!item->toSong()) return QStyledItemDelegate::createEditor(parent, option, index);
    RatingWidget *editor = new RatingWidget(parent);
    connect(editor, SIGNAL(editingCompleted()), this, SLOT(commitChanges()));
    return editor;
}

void RatingDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    Item *item = static_cast<Item *>(index.internalPointer());
    if (!item->toSong()) return QStyledItemDelegate::setEditorData(editor, index);
    int rating = item->toSong()->rating();
    RatingWidget *widget = static_cast<RatingWidget*>(editor);
    widget->setRating(rating);
}

void RatingDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    Item *item = static_cast<Item *>(index.internalPointer());
    if (!item->toSong()) return QStyledItemDelegate::setModelData(editor, model, index);
    RatingWidget *widget = static_cast<RatingWidget*>(editor);
    int rating = widget->rating();
    item->toSong()->setRating(rating);
    emit model->dataChanged(index, index);
}

void RatingDelegate::commitChanges(){
    RatingWidget *widget = static_cast<RatingWidget*>(sender());
    commitData(widget);
    closeEditor(widget);
}
