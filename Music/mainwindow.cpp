#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Музыкальная коллекция[*]");

    model = new MusicModel;
    ui->treeView->setModel(model);
    const int RatingColumn = 2;

    RatingDelegate *delegate = new RatingDelegate;
    ui->treeView->setItemDelegateForColumn(RatingColumn, delegate);

    ui->editAction->setEnabled(false);
    ui->deleteAction->setEnabled(false);
    ui->addAlbumAction->setEnabled(false);
    ui->addSongAction->setEnabled(false);

    connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(setModified()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateActions(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModified(){
    setWindowModified(true);
}

void MainWindow::updateActions(const QModelIndex &index){
    Item *item = static_cast<Item *>(index.internalPointer());
    if (!(item && index.isValid())){
        ui->editAction->setEnabled(false);
        ui->deleteAction->setEnabled(false);
        ui->addAlbumAction->setEnabled(false);
        ui->addSongAction->setEnabled(false);
        return;
    }
    else if (item->toArtist()){
        ui->editAction->setEnabled(true);
        ui->deleteAction->setEnabled(true);
        ui->addAlbumAction->setEnabled(true);
        ui->addSongAction->setEnabled(false);
    }
    else if (item->toAlbum()){
        ui->editAction->setEnabled(true);
        ui->deleteAction->setEnabled(true);
        ui->addAlbumAction->setEnabled(false);
        ui->addSongAction->setEnabled(true);
    }
    else if (item->toSong()){
        ui->editAction->setEnabled(true);
        ui->deleteAction->setEnabled(true);
        ui->addAlbumAction->setEnabled(false);
        ui->addSongAction->setEnabled(false);
    }
}

void MainWindow::on_addArtistAction_triggered()
{
    bool was_modified = isWindowModified();
    ArtistDialog *dialog = new ArtistDialog(this);
    bool status = dialog->addArtist(model, QModelIndex());
    if(was_modified)return;
    else if(status) setModified();
}

void MainWindow::on_editAction_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    Item *item = static_cast<Item *>(cur_index.internalPointer());
    if(item->toArtist()){
        ArtistDialog *dialog = new ArtistDialog(this);
        dialog->setModel(model);
        dialog->setModelIndex(cur_index);
        dialog->show();
    }
    else if(item->toAlbum()){
        AlbumDialog *dialog = new AlbumDialog(this);
        dialog->setModel(model);
        dialog->setModelIndex(cur_index);
        dialog->show();
    }
}

void MainWindow::on_addAlbumAction_triggered()
{
    bool was_modified = isWindowModified();
    AlbumDialog *dialog = new AlbumDialog(this);
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    bool status = dialog->addAlbum(model, cur_index);
    if(was_modified)return;
    else if(status) setModified();
}

void MainWindow::on_addSongAction_triggered()
{
    bool was_modified = isWindowModified();
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    Album *album = static_cast<Item *>(cur_index.internalPointer())->toAlbum();
    bool status = model->insertRow(album->childCount(), cur_index);
    if(was_modified)return;
    else if(status) setModified();
}

void MainWindow::on_deleteAction_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    model->removeRow(cur_index.row(), cur_index.parent());
    setModified();
    updateActions(ui->treeView->selectionModel()->currentIndex());
}

bool MainWindow::on_saveAction_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить как", QDir::currentPath(), "Databases (*.db)");
    QFile file(filename);
    if (filename.isEmpty()) return false;
    else if (file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);
        stream << *(model->m_root);
        file.close();
        setWindowModified(false);
        return true;
    }
    return false;
}

bool MainWindow::on_openAction_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Открыть", QDir::currentPath(), "Databases (*.db)");
    QFile file(filename);
    if (filename.isEmpty()) return false;
    else if (file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        delete model->m_root;
        ui->treeView->reset();
        Item *item = new Item;
        stream >> *(item);
        file.close();
        model->m_root = item;
        setWindowModified(false);
        return true;
    }
    return false;
}

void MainWindow::on_exitAction_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isWindowModified()){
        event->accept();
        return;
    }
    QString save = "Сохранить";
    QString no_save = "Не сохранять";
    QString cancel = "Отмена";
    QMessageBox messageBox(QMessageBox::Question,
                "Музыкальная коллекция",
                "Сохранить изменения в файле?",
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                this);
    messageBox.setButtonText(QMessageBox::Save, save);
    messageBox.setButtonText(QMessageBox::Discard, no_save);
    messageBox.setButtonText(QMessageBox::Cancel, cancel);
    int res = messageBox.exec();
    switch(res){
        case QMessageBox::Save:
        {
            bool result = on_saveAction_triggered();
            result ? event -> accept(): event -> ignore();
            break;
        }
        case QMessageBox::Discard:
            event -> accept();
            break;
        case QMessageBox::Cancel:
            event -> ignore();
            break;
    }
}
