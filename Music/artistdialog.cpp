#include "artistdialog.h"
#include "ui_artistdialog.h"

ArtistDialog::ArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtistDialog)
{
    ui->setupUi(this);
    setWindowTitle("Исполнитель");
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
}

ArtistDialog::~ArtistDialog()
{
    delete ui;
}

void ArtistDialog::setModel(MusicModel* model){
    m_mapper.setModel(model);
}

void ArtistDialog::setModelIndex(const QModelIndex &index){
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    Artist *artist = static_cast<Item *>(index.internalPointer())->toArtist();
    _artist = artist;
    m_mapper.addMapping(ui->name, 0);
    ui->name->setText(artist->name());
    m_mapper.addMapping(ui->country, 1);
    ui->country->setText(artist->country());
    m_mapper.addMapping(ui->comment, 2);
    ui->comment->setPlainText(artist->comment());
    m_mapper.addMapping(ui->picture, 3);
    if (!artist->picture().isNull()){
        ui->picture->setPixmap(artist->picture().scaled(100, 100, Qt::KeepAspectRatioByExpanding).copy(QRect(QPoint(0, 0), QSize(100, 100))));
        _picture = artist->picture();
    }
}

void ArtistDialog::accept() {
    m_mapper.submit();
    _artist->setPicture(_picture);
    QDialog::accept();
}

bool ArtistDialog::addArtist(MusicModel *model, const QModelIndex &parent) {
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

void ArtistDialog::on_browse_clicked(){
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
