#ifndef ITEM_H
#define ITEM_H
#include <QList>
#include <QPixmap>
#include <QTime>
#include <QDataStream>

class Artist;
class Album;
class Song;

class Item {
public:
    Item();
    Item(const QString &);
    ~Item();
    Item *parent() const;
    void setParent(Item *);
    void insertChild(Item *, int position = -1);
    Item *takeChild(int);
    Item *childAt(int) const;
    int indexOf(Item*) const;
    int childCount() const;
    QString name() const{ return m_name; }
    void setName(const QString & _name){ m_name = _name; }
    virtual Artist *toArtist() { return 0; }
    virtual Album *toAlbum() { return 0; }
    virtual Song *toSong() { return 0; }
private:
    Item *m_parent;
    QList<Item*> m_children;
    QString m_name;
    QString m_comment;
};

class Artist : public Item{
    QPixmap _picture;
    QString _country;
    QString _comment;
public:
    Artist() : Item() {}
    Artist(const QString &n) : Item(n) {}
    const QPixmap picture() const{ return _picture; }
    void setPicture(const QPixmap &_p) { _picture = _p; }
    const QString country() const{ return _country; }
    void setCountry(const QString &_c) { _country = _c; }
    const QString comment() const{ return _comment; }
    void setComment(const QString &_c) { _comment = _c; }
    Artist *toArtist() { return this; }
    Album *toAlbum() { return 0; }
    Song *toSong() { return 0; }
};

class Album : public Item{
    int _year;
    QPixmap _picture;
    QString _genre;
    QString _comment;
public:
    Album() : Item() { setYear(2000); }
    Album(const QString &n) : Item(n) { setYear(2000); }
    int year() const{ return _year; }
    void setYear(int _y) { _year = _y; }
    const QPixmap picture() const{ return _picture; }
    void setPicture(const QPixmap &_p) { _picture = _p; }
    const QString genre() const{ return _genre; }
    void setGenre(const QString &_g) { _genre = _g; }
    const QString comment() const{ return _comment; }
    void setComment(const QString &_c) { _comment = _c; }
    Artist *toArtist() { return 0; }
    Album *toAlbum() { return this; }
    Song *toSong() { return 0; }
};

class Song : public Item{
    QTime _time;
    int _rating;
    QString _comment;
public:
    Song() : Item() { setRating(0); }
    Song(const QString &n) : Item(n) { setRating(0); }
    const QTime time() const{ return _time; }
    void setTime(const QTime &_t) { _time = _t; }
    int rating() const{ return _rating; }
    void setRating(int _r) { _rating = _r; }
    QString comment() const{ return _comment; }
    void setComment(const QString &_c) { _comment = _c; }
    Artist *toArtist() { return 0; }
    Album *toAlbum() { return 0; }
    Song *toSong() { return this; }
};

QDataStream& operator<<(QDataStream &, const Artist &);
QDataStream& operator<<(QDataStream &, const Album &);
QDataStream& operator<<(QDataStream &, const Song &);
QDataStream& operator>>(QDataStream &, Artist &);
QDataStream& operator>>(QDataStream &, Album &);
QDataStream& operator>>(QDataStream &, Song &);
QDataStream& operator<<(QDataStream &stream, const Item &item);
QDataStream& operator>>(QDataStream &stream, Item &item);
#endif // ITEM_H
