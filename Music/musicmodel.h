#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include <QAbstractItemModel>
#include <item.h>

class MusicModel : public QAbstractItemModel
{
public:
    Item *m_root;
    MusicModel();
    MusicModel(Item *_m_root){ m_root = _m_root;};
    ~MusicModel();
    QModelIndex	index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex	parent(const QModelIndex &index) const;
    int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    int	columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

#endif // MUSICMODEL_H
