#include "configurationdialog.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    ui->frame->setFrameShape(QFrame::Box);
    QPushButton *cancel = ui->buttonBox->button(QDialogButtonBox::Cancel);
    cancel->setText(QString("Отмена"));
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::on_browse_button_clicked()
{
    QString selectedFilter("Images ");
    QList<QByteArray> format_list = QImageReader::supportedImageFormats();
    selectedFilter += "(*." + format_list.join(" *.") + ")";
    file_name = QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::currentPath(), selectedFilter);
    if (!file_name.isEmpty()) ui->line_edit->setText(file_name);
    ui->frame->setPixmap(QPixmap(file_name));
    return;
}

QString ConfigurationDialog::imageFilePath(){
    return file_name;
}

QSize ConfigurationDialog::puzzleSize(){
    return ui->frame->sizeHint();
}

void ConfigurationDialog::accept(){
    if (QPixmap(file_name).isNull()){
        QMessageBox::warning(0, QString("Предупреждение!"), QString("Вы не выбрали изображение!"));
        emit ui->browse_button->clicked();
    }
    if (!QPixmap(file_name).isNull()){
        QGraphicsView *view = new QGraphicsView;
        GameLogic *g = new GameLogic;
        g->setup(ui->frame->value(), QPixmap(file_name));
        view->setScene(g);
        view->show();
    }
    QDialog::accept();
}
