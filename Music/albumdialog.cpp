#include "albumdialog.h"
#include "ui_albumdialog.h"

AlbumDialog::AlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    setWindowTitle("Альбом");
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    ui->name_artist->setReadOnly(true);
}

AlbumDialog::~AlbumDialog()
{
    delete ui;
}

void AlbumDialog::setModel(MusicModel* model){
    m_mapper.setModel(model);
}

void AlbumDialog::setModelIndex(const QModelIndex &index){
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    Album *album = static_cast<Item *>(index.internalPointer())->toAlbum();
    _album = album;
    ui->name_artist->setText(static_cast<Item *>(parent.internalPointer())->toArtist()->toArtist()->name());
    m_mapper.addMapping(ui->name, 0);
    ui->name->setText(album->name());
    m_mapper.addMapping(ui->year, 1);
    ui->year->setValue(album->year());
    m_mapper.addMapping(ui->genre, 2);
    ui->genre->setText(album->genre());
    ui->comment->setPlainText(album->comment());
    m_mapper.addMapping(ui->comment, 3);
    if (!album->picture().isNull()){
        ui->picture->setPixmap(album->picture().scaled(100, 100, Qt::KeepAspectRatioByExpanding).copy(QRect(QPoint(0, 0), QSize(100, 100))));
        _picture = album->picture();
    }
}

void AlbumDialog::accept() {
    m_mapper.submit();
    _album->setPicture(_picture);
    QDialog::accept();
}

bool AlbumDialog::addAlbum(MusicModel *model, const QModelIndex &parent) {
        setModel(model);
        int row = model->rowCount(parent);
        if(!model->insertRow(row, parent))
            return false;
        QModelIndex index = model->index(row, 0, parent);
        setModelIndex(index);
        if(!exec()){
            model->removeRow(row, parent);
            return false;
        }
        return true;
    }

void AlbumDialog::on_browse_clicked(){
    QString selectedFilter("Images ");
    QList<QByteArray> format_list = QImageReader::supportedImageFormats();
    selectedFilter += "(*." + format_list.join(" *.") + ")";
    QString filename = QFileDialog::getOpenFileName(this, "Открыть", QDir::currentPath(), selectedFilter);
    if (filename.isEmpty()) return;
    else{
        if (!_picture.load(filename)){
            QMessageBox::warning(this, tr("Ошибка"), tr("Изображение не может быть открыто."),  QMessageBox::Close);
            return;
        }
        ui->picture->setPixmap(_picture.scaled(100, 100, Qt::KeepAspectRatioByExpanding).copy(QRect(QPoint(0, 0), QSize(100, 100))));
    }
}
