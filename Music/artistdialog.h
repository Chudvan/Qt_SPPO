#ifndef ARTISTDIALOG_H
#define ARTISTDIALOG_H

#include <QDialog>
#include <QAbstractItemModel>
#include <QDataWidgetMapper>
#include <musicmodel.h>
#include <QFileDialog>
#include <QImageReader>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ArtistDialog;
}

class ArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistDialog(QWidget *parent = nullptr);
    ~ArtistDialog();
    void setModel(MusicModel*);
    void setModelIndex(const QModelIndex &);
    bool addArtist(MusicModel *model, const QModelIndex &parent);
    void accept();
private slots:
    void on_browse_clicked();

private:
    Ui::ArtistDialog *ui;
    QDataWidgetMapper m_mapper;
    QPixmap _picture;
    Artist *_artist;
};

#endif // ARTISTDIALOG_H
