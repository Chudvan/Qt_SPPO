#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    connect_clipboard();
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    settings = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME);
    QString viewFont = "viewFont";
    QFont default_font(DEFAULT_FONT, DEFAULT_FONT_SIZE);
    QFont last_font = qvariant_cast<QFont>(settings -> value(viewFont, default_font));
    ui -> textEdit -> setFont(last_font);
    m_fileName = QString();
    setFileName(m_fileName);
}

MainWindow::MainWindow(const QString& filename, QWidget *parent)
    : MainWindow(parent)
{
    m_fileName = filename;
    loadFile(m_fileName);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    MainWindow* w1 = new MainWindow;
    w1 -> show();
}

void MainWindow::on_textEdit_textChanged()
{
    documentModified();
}

void MainWindow::documentModified()
{
    setWindowModified(true);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (! this -> isWindowModified()) e -> accept();
    else{
        QString title = tr("TextEditor");
        QString text = tr("Сохранить изменения в файле %1?").arg(m_fileName);
        QString save = tr("Сохранить");
        QString no_save = tr("Не сохранять");
        QString cancel = tr("Отмена");
        QMessageBox messageBox(QMessageBox::Question,
                    title,
                    text,
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                    this);
        messageBox.setButtonText(QMessageBox::Save, save);
        messageBox.setButtonText(QMessageBox::Discard, no_save);
        messageBox.setButtonText(QMessageBox::Cancel, cancel);
        int res = messageBox.exec();
        switch(res){
            case QMessageBox::Save:
            {
                bool result;
                if (m_fileName.isNull()) result = saveFileAs();
                else result = saveFile();
                result ? e -> accept(): e -> ignore();
                break;
            }
            case QMessageBox::Discard:
                e -> accept();
                break;
            case QMessageBox::Cancel:
                e -> ignore();
                break;
        }
    }
}

void MainWindow::on_actionSelectFont_triggered()
{
    bool ok;
    QString viewFont = "viewFont";
    QFont last_font = qvariant_cast<QFont>(settings -> value(viewFont));
    QFont font = QFontDialog::getFont(&ok, last_font, this);
    if (ok){
        ui->textEdit->setFont(font);
        settings -> setValue(viewFont, font);
    }
}

void MainWindow::connect_clipboard(){
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->textEdit, SLOT(paste()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->textEdit, SLOT(redo()));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));
}

void MainWindow::on_actionAbout_triggered()
{
    QString title = QString("О программе");
    QString done_by = QString("Выполнил: Чудновец Иван Владимирович\nГруппа: Б17-511");
    QMessageBox::about(this, title, done_by);
}

void MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Ошибка"), tr("Ошибка: не удалось открыть файл."));
        setFileName(QString());
    }
    else{
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
        setFileName(fileName);
        this -> setWindowModified(false);
    }
}

void MainWindow::setFileName(const QString &fileName){
    m_fileName = fileName;
    QString title = QString("%1[*] - %2")
            .arg(m_fileName.isNull()?"Новый документ":QFileInfo(m_fileName).fileName())
            .arg(QApplication::applicationName());
    this ->setWindowTitle(title);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            "Открыть документ", QDir::currentPath(), "Text documents (*.txt)");
    if (fileName.isNull()) return;
    else{
        if (!this->isWindowModified()){
            loadFile(fileName);
        }
        else{
            MainWindow* w = new MainWindow(fileName);
            w -> show();
        }
    }
}

bool MainWindow::saveFileAs(){
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить документ",
          m_fileName.isNull()?QDir::currentPath():m_fileName, "Text documents (*.txt)");
    if (fileName.isNull())return false;
    setFileName(fileName);
    return saveFile();
}

bool MainWindow::saveFile(){
    if (m_fileName.isNull())return saveFileAs();
    QFile file(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Ошибка"), tr("Ошибка: не удалось открыть файл."));
        setFileName(QString());
        return false;
    }
    QTextStream in(&file);
    in << ui->textEdit->toPlainText();
    file.close();
    this ->setWindowModified(false);
    return true;
}
