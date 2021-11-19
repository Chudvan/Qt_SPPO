#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <musicmodel.h>
#include <ratingdelegate.h>
#include <artistdialog.h>
#include <albumdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();
public slots:
    void setModified();
    void updateActions(const QModelIndex &index);
private slots:
    void on_addArtistAction_triggered();

    void on_editAction_triggered();

    void on_addAlbumAction_triggered();

    void on_addSongAction_triggered();

    void on_deleteAction_triggered();

    bool on_saveAction_triggered();

    bool on_openAction_triggered();

    void on_exitAction_triggered();

private:
    Ui::MainWindow *ui;
    MusicModel *model;
};
#endif // MAINWINDOW_H
