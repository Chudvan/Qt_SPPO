#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <QImageReader>
#include <QDebug>
#include <puzzlepiece.h>
#include <gamelogic.h>
#include <QGraphicsView>


namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog() override;

    QString imageFilePath();
    QSize puzzleSize();

private slots:
    void on_browse_button_clicked();
    void accept() override;

private:
    Ui::ConfigurationDialog *ui;
    QString file_name;
};

#endif // CONFIGURATIONDIALOG_H
