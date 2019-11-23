#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define DEFAULT_FONT "Cooper Black"
#define DEFAULT_FONT_SIZE 12
#define APPLICATION_NAME "TextEditor"
#define APPLICATION_VERSION "0.1"
#define ORGANIZATION_NAME "MephiSoft"
#define ORGANIZATION_DOMAIN "mephi.ru"

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QFontDialog>
#include <QSettings>
#include <QTextStream>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>
#include <QStringBuilder>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow(const QString& filename, QWidget *parent = 0);

    QSettings *settings;

private slots:
    void on_actionNew_triggered();

    void on_textEdit_textChanged();

    void closeEvent(QCloseEvent *);

    void on_actionSelectFont_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    bool saveFile();

    bool saveFileAs();

private:
    void documentModified();

    void connect_clipboard();

    void loadFile(const QString &);

    void setFileName(const QString &);

    QString m_fileName;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
