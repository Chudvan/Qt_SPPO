#include "mainwindow.h"
#include <QList>
#include <QApplication>
#include <QDebug>
#include <item.h>
#include <QDataStream>
#include <QFileDialog>
#include <QTreeView>
#include <musicmodel.h>
#include <QAbstractItemModelTester>
#include <QHeaderView>
#include <ratingdelegate.h>
#include <artistdialog.h>
#include <albumdialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
//    MainWindow w;
//    w.show();
//    QList<int> l;
//    l.append(1);
//    l.append(2);
//    l.insert(-10, 0);
//    qDebug() << l.takeAt(0);
//    qDebug() << l.takeAt(0);
//    qDebug() << l.indexOf(1);
    Item *_m1 = new Artist;
    Artist *m1 = _m1->toArtist();
    m1->setComment("comment0");
    m1->setCountry("RUSSIA");
    m1->setPicture(QPixmap("C:/Users/Public/Pictures/Sample Pictures/Chrysanthemum.jpg"));
    m1->setName("ИМЯ");
    Item *_m2 = new Album("m2");
    Album *m2 = _m2->toAlbum();
    m2->setComment("comment1");
    m2->setYear(1993);
    m2->setGenre("ROCK");
//    QString name = QFileDialog::getOpenFileName(0, "Open", QDir::currentPath());
//    qDebug() << name;
//    m2->setPicture(QPixmap(name));
    m2->setPicture(QPixmap("C:/Users/Public/Pictures/Sample Pictures/Chrysanthemum.jpg"));
    Album *m3 = new Album("m3");
    Album *m4 = new Album("m4");
    Item *_m5 = new Song("m5");
    Song *m5 = _m5->toSong();
    m5->setTime(QTime(0, 3, 26, 0));
    m5->setRating(4);
    m5->setComment("comment2");
    Song *m6 = new Song("m6");
    m1->insertChild(m2);
//    m1->insertChild(m4);
    m4->setParent(m1);
    m2->insertChild(m5);
    m4->insertChild(m6);
    m1->insertChild(m3, 1);
//    m6->setParent(m3);
    qDebug() << m1->childCount();
//    qDebug() << m1->childAt(1)->name();
//    delete m4;
//    qDebug() << m3->parent() << m3 << m3->childCount() << m3->name();
//    Item *cur;
//    qDebug() << m1->childAt(0)->name();
//    cur = m1->takeChild(0);
//    qDebug() << cur->name() << cur->parent() << "cur";
//    qDebug() << m1->indexOf(m4) << "index";
    qDebug() << m1->childAt(0)->name() << m1->childAt(0)->toAlbum() << m1->comment() << m1->country() << m1->picture();
    qDebug() << m2->year() << m2->comment() << m2->picture() << m2->genre();
    qDebug() << m1->parent() << m1 << m1->childCount() << m1->name();
    qDebug() << m2->parent()->name() << m2 << m2->childCount() << m2->name();
    qDebug() << m3->parent()->name() << m3 << m3->childCount() << m3->name();
    qDebug() << m4->parent()->name() << m4 << m4->childCount() << m4->name();
    qDebug() << m5->parent()->name() << m5 << m5->childCount() << m5->name()
             << m5->time() << m5->rating() << m5->comment();
    qDebug() << (m5 == nullptr);
    qDebug() << m6->parent()->name() << m6 << m6->childCount() << m6->name();
    qDebug() << m1->childAt(1)->name();
    QFile file("D:/Qt/Code/Music/new.txt");
    QDataStream stream(&file);
    if (file.open(QIODevice::WriteOnly)){
        stream << *m1;
    }
    file.close();
    Artist *artist = new Artist;
    if (file.open(QIODevice::ReadOnly)){
        stream >> *artist;
    }
    file.close();
    qDebug() << "Deserialization";
    qDebug() << artist->childCount();
    qDebug() << artist->childAt(0)->name() << artist->childAt(0)->toAlbum()
             << artist->comment() << artist->country() << artist->picture();
    Album *album_1;
    album_1 = artist->childAt(0)->toAlbum();
    qDebug() << album_1->year() << album_1->comment()
             << album_1->picture() << album_1->genre();
    qDebug() << artist->parent() << artist << artist->childCount() << artist->name();
    qDebug() << album_1->parent()->name() << album_1
             << album_1->childCount() << album_1->name();
    Album *album_2;
    album_2 = artist->childAt(1)->toAlbum();
    qDebug() << album_2->parent()->name() << album_2
             << album_2->childCount() << album_2->name();
    Album *album_3;
    album_3 = artist->childAt(2)->toAlbum();
    qDebug() << album_3->parent()->name() << album_3
             << album_3->childCount() << album_3->name();
    Song *song_1, *song_2;
    song_1 = album_1->childAt(0)->toSong();
    qDebug() << song_1->parent()->name() << song_1 << song_1->childCount()
             << song_1->name() << song_1->time() << song_1->rating()
             << song_1->comment();
    qDebug() << (song_1 == nullptr);
    song_2 = album_3->childAt(0)->toSong();
    qDebug() << song_2->parent()->name() << song_2
             << song_2->childCount() << song_2->name();
    qDebug() << artist->childAt(1)->name();

    Item *root = new Item;
    root->insertChild(artist);
    Artist *artist2 = new Artist;
    artist2->setName("Second_a");
    artist2->setParent(root);
    MusicModel *model = new MusicModel(root);
    QModelIndex index_a1 = model->index(0,0,QModelIndex());
    QModelIndex index_a2 = model->index(1,0,QModelIndex());
    Album *album4 = new Album("4-ый");
    artist->insertChild(album4);
    qDebug() << "Артист 1" << static_cast<Item*>((index_a1).internalPointer())->name()
             << "Родитель" << static_cast<Item*>((model->parent(index_a1)).internalPointer())
             << "Строк" << model->rowCount(index_a1) << "Колонок" << model->columnCount(index_a1);
    qDebug() << "Артист 2" << static_cast<Item*>((index_a2).internalPointer())->name()
             << "Строк" << model->rowCount(index_a2) << "Колонок" << model->columnCount(index_a2);
    QModelIndex index_a_1_1 = model->index(0, 0, index_a1);
    qDebug() << "Альбом 1" << static_cast<Item*>((index_a_1_1).internalPointer())->name()
             << "Родитель" << static_cast<Item*>((model->parent(index_a_1_1)).internalPointer())->name()
             << "Строк" << model->rowCount(index_a_1_1) << "Колонок" << model->columnCount(index_a_1_1);
    QModelIndex index_a_1_2 = model->index(1, 0, index_a1);
    qDebug() << "Альбом 2" << static_cast<Item*>((index_a_1_2).internalPointer())->name()
             << "Строк" << model->rowCount(index_a_1_2) << "Колонок" << model->columnCount(index_a_1_2);
    QModelIndex index_a_1_3 = model->index(2, 0, index_a1);
    qDebug() << "Альбом 3" << static_cast<Item*>((index_a_1_3).internalPointer())->name()
             << "Строк" << model->rowCount(index_a_1_3) << "Колонок" << model->columnCount(index_a_1_3);
    QModelIndex index_a_2_1 = model->index(0, 0, index_a_1_1);
    qDebug() << "Песня 1" << static_cast<Item*>((index_a_2_1).internalPointer())->name()
             << "Родитель" << static_cast<Item*>((model->parent(index_a_2_1)).internalPointer())->name()
             << "Строк" << model->rowCount(index_a_2_1) << "Колонок" << model->columnCount(index_a_2_1);
//    model->removeRow(1, QModelIndex());
    model->insertRow(0, index_a_1_2);
    model->insertRow(1, QModelIndex());
    /*
    if (file.open(QIODevice::WriteOnly)){
        stream << *root;
    }
    file.close();
    Item *item_2 = new Item;
    if (file.open(QIODevice::ReadOnly)){
        stream >> *item_2;
    }
    file.close();
    MusicModel *model2 = new MusicModel(item_2);
    Конец

//    new QAbstractItemModelTester(model2, QAbstractItemModelTester::FailureReportingMode::Fatal, 0);

    QTreeView *tree = new QTreeView;

    ArtistDialog *a_dialog = new ArtistDialog;
    a_dialog->setModel(model);
    a_dialog->setModelIndex(index_a1);
    a_dialog->show();

    AlbumDialog *al_dialog = new AlbumDialog;
    al_dialog->setModel(model);
    al_dialog->setModelIndex(index_a_1_1);
    al_dialog->show();
    const int RatingColumn = 2; // возможно в вашей модели это будет
                            // другой номер колонки

    RatingDelegate *delegate = new RatingDelegate;
    tree->setItemDelegateForColumn(RatingColumn, delegate);

    tree->setModel(model);
    tree->show();
    /*
    QFile file("D:/Qt/Code/Music/new.txt");
    QDataStream stream(&file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)){
        stream << QString("ads") << 123 << QString("last");
        if (stream.status() != QDataStream::Ok){
            qDebug() << "Ошибка записи.";
        }
    }
    file.close();
    QString first, last, another;
    int middle;
    if (file.open(QIODevice::ReadOnly)){
        stream >> first >> middle >> last >> another;
//        stream >> middle;
//        stream >> last;
//        stream >> another;
    }
    qDebug() << first << middle << last << another;
    file.close();
    */
    MainWindow m;
    m.show();
    return a.exec();
}
