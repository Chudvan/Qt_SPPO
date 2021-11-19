#include "musicmodel.h"
#include <QDebug>

MusicModel::MusicModel()
{
    m_root = new Item;
}

MusicModel::~MusicModel(){
    delete m_root;
}

QModelIndex MusicModel::index(int row,int column,const QModelIndex &parent) const
{
    Item *parentItem = m_root;

    if(parent.isValid())
        parentItem = static_cast<Item*>(parent.internalPointer());
    if (parentItem->childAt(row))
        return createIndex(row, column, parentItem->childAt(row));

    return QModelIndex();
}

QModelIndex	MusicModel::parent(const QModelIndex &index) const{
    if (!index.isValid())return QModelIndex();
    Item *childItem = static_cast<Item *>(index.internalPointer());
    Item *parent = childItem->parent();
    if ((parent == m_root) || !(parent)) return QModelIndex();
    Item *grandparent = parent->parent();
    return createIndex(grandparent->indexOf(parent), 0, parent);
}

int	MusicModel::rowCount(const QModelIndex &parent) const{
    Item *parentItem = m_root;
    if(parent.isValid())
        parentItem = static_cast<Item *>(parent.internalPointer());
    return parentItem->childCount();
}

int	MusicModel::columnCount(const QModelIndex &parent) const{
    return 4;
}

QVariant MusicModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.isValid()){
            int column = index.column();
            Item *item = static_cast<Item *>(index.internalPointer());
            switch (column){
            case 0:
                return item->name();
            case 1:
                if(item->toArtist()) return item->toArtist()->country();
                if(item->toAlbum()) return item->toAlbum()->year();
                if(item->toSong()) return item->toSong()->time();
                break;
            case 2:
                if(item->toArtist()) return item->toArtist()->comment();
                if(item->toAlbum()) return item->toAlbum()->genre();
                if(item->toSong()) return item->toSong()->rating();
                break;
            case 3:
                if(item->toArtist()) return item->toArtist()->picture();
                if(item->toAlbum()) return item->toAlbum()->comment();
                if(item->toSong()) return item->toSong()->comment();
                break;
            }
        }
        return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole)){
        Item *element = static_cast<Item *>(index.internalPointer());
        int column = index.column();
        switch (column){
        case 0:
            element->setName(value.toString());
            break;
        case 1:
            if (element->toArtist())element->toArtist()->setCountry(value.toString());
            if (element->toAlbum())element->toAlbum()->setYear(value.toInt());
            if (element->toSong())element->toSong()->setTime(value.toTime());
            break;
        case 2:
            if(element->toArtist()) element->toArtist()->setComment(value.toString());
            if(element->toAlbum()) element->toAlbum()->setGenre(value.toString());
            if(element->toSong()) element->toSong()->setRating(value.toInt());
            break;
        case 3:
            if(element->toAlbum()) element->toAlbum()->setComment(value.toString());
            if(element->toSong()) element->toSong()->setComment(value.toString());
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool MusicModel::insertRow(int row, const QModelIndex &parent){
    Item *parentItem = m_root;
    if (parent.isValid())
        parentItem = static_cast<Item *>(parent.internalPointer());
    Item *child;
    if (parentItem == m_root)child = new Artist;
    else if (parentItem->toArtist()) child = new Album;
    else if (parentItem->toAlbum()) child = new Song;
    beginInsertRows(parent, row, row);
    parentItem->insertChild(child, row);
    endInsertRows();
    return true;
}

bool MusicModel::removeRow(int row, const QModelIndex &parent){
    Item *parentItem = m_root;
    if (parent.isValid())
        parentItem = static_cast<Item *>(parent.internalPointer());
    beginRemoveRows(parent, row, row);
    parentItem->takeChild(row);
    endRemoveRows();
    return true;
}

QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole){
        switch(section){
        case 0:
            return QString("Трек");
        case 1:
            return QString("Продолжительность");
        case 2:
            return QString("Рейтинг");
        case 3:
            return QString("Заметки");
        }
    }
    return QVariant();
}
