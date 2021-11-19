#include "item.h"
#include <QDebug>


Item::Item(){
    m_parent = 0;
    m_name = "Безымянный";
}

Item::Item(const QString &name){
    m_parent = 0;
    m_name = name;
}

Item::~Item(){
    int count = childCount();
    if (m_parent)m_parent->m_children.takeAt(m_parent->indexOf(this));
    for (int i = 0; i < count; i++) delete childAt(0);
}

void Item::insertChild(Item *child, int position){
    if(position < 0)position = childCount();
    if (!m_children.contains(child))m_children.insert(position, child);
    if (child->parent() != this)child->setParent(this);
}

Item *Item::takeChild(int position){
    Item *child = m_children.takeAt(position);
    child->setParent(0);
    return child;
}

void Item::setParent(Item *_parent){
    if (_parent){
        if (m_parent){
            m_parent->takeChild(m_parent->indexOf(this));
        }
        m_parent = _parent;
        m_parent->insertChild(this);
    }
    m_parent = _parent;
}

Item *Item::parent() const{
    return m_parent;
}


Item *Item::childAt(int position) const{
    if (position < 0 || position >= childCount()) return nullptr;
    return m_children.at(position);
}

int Item::indexOf(Item* el) const{
    return m_children.indexOf(el);
}

int Item::childCount() const{
    return m_children.size();
}

QDataStream& operator<<(QDataStream &stream, const Artist &artist) {

    stream << artist.name() << artist.picture() << artist.country()
           << artist.comment();
    // serialize children
    int cnt = artist.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i){
        Album *album = artist.childAt(i)->toAlbum();
        if(album) stream << *album;
    }
    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Album &album){

    stream << album.name() << album.year() << album.picture()
           << album.genre() << album.comment();
    int cnt = album.childCount();
    stream << cnt;
    for (int i = 0; i < cnt; i++){
        Song *song = album.childAt(i)->toSong();
        if (song) stream << *song;
    }
    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Song &song){

    stream << song.name() << song.time() << song.rating()
           << song.comment();
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Artist &artist){
    QString name;
    QPixmap picture;
    QString country;
    QString comment;
    stream >> name >> picture >> country >> comment;
    artist.setName(name);
    artist.setPicture(picture);
    artist.setCountry(country);
    artist.setComment(comment);
    int cnt;
    stream >> cnt;
    Album *album;
    for (int i = 0; i < cnt; i++){
        album = new Album;
        stream >> *album;
        artist.insertChild(album);
    }
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Album &album){
    QString name;
    int year;
    QPixmap picture;
    QString genre;
    QString comment;
    stream >> name >> year >> picture >> genre >> comment;
    album.setName(name);
    album.setYear(year);
    album.setPicture(picture);
    album.setGenre(genre);
    album.setComment(comment);
    int cnt;
    stream >> cnt;
    Song *song;
    for (int i = 0; i < cnt; i++){
        song = new Song;
        stream >> *song;
        album.insertChild(song);
    }
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Song &song){
    QString name;
    QTime time;
    int rating;
    QString comment;
    stream >> name >> time >> rating >> comment;
    song.setName(name);
    song.setTime(time);
    song.setRating(rating);
    song.setComment(comment);
    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Item &item) {

    int cnt = item.childCount();
    stream << cnt;
    for(int i=0; i<cnt; ++i){
        Artist *artist = item.childAt(i)->toArtist();
        if(artist) stream << *artist;
    }
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Item &item){
    int cnt;
    stream >> cnt ;
    Artist *artist;
    for (int i = 0; i < cnt; i++){
        artist = new Artist;
        stream >> *artist;
        item.insertChild(artist);
    }
    return stream;
}
