#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include <QAbstractItemModel>
#include <QDataWidgetMapper>
#include <musicmodel.h>
#include <QFileDialog>
#include <QImageReader>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *parent = nullptr);
    ~AlbumDialog();
    void setModel(MusicModel*);
    void setModelIndex(const QModelIndex &);
    bool addAlbum(MusicModel *model, const QModelIndex &parent);
    void accept();
private slots:
    void on_browse_clicked();

private:
    Ui::AlbumDialog *ui;
    QDataWidgetMapper m_mapper;
    QPixmap _picture;
    Album *_album;
};

#endif // ALBUMDIALOG_H
