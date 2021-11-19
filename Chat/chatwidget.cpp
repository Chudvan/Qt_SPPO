#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QString name, quint16 port, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    user_name = name;
    _port = port;
    socket = new QUdpSocket;
    socket->bind(_port, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    QByteArray data = encodeMessage(user_name, START_CHAT);
    socket->writeDatagram(data, QHostAddress::Broadcast, _port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
    setWindowTitle(QString("easy talk [%1@%2]").arg(user_name).arg(QString::number(_port)));
    isNew = true;
}

ChatWidget::~ChatWidget()
{
    delete ui;
    QByteArray data = encodeMessage(user_name, END_CHAT);
    socket->writeDatagram(data, QHostAddress::Broadcast, _port);
    delete socket;
}

QByteArray ChatWidget::encodeMessage(const QString &name, const QString &message){
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << name << message;
    return array;
}

QPair<QString, QString> ChatWidget::decodeMessage(QByteArray& data){
    QDataStream stream(&data, QIODevice::ReadOnly);
    QString name, message;
    stream >> name >> message;
    return qMakePair(name, message);
}

void ChatWidget::sendMessage(){
    QByteArray data = encodeMessage(user_name, ui->lineEdit->text());
    socket->writeDatagram(data, QHostAddress::Broadcast, _port);
    ui->lineEdit->setText("");
}

void ChatWidget::readPendingDatagrams(){
    QByteArray data;
    while (socket->hasPendingDatagrams()){
        data.resize(socket->pendingDatagramSize());
        socket->readDatagram(data.data(), data.size());
        QPair<QString, QString> pair = decodeMessage(data);
        QString name = pair.first, message = pair.second;
        if (message == START_CHAT){
            if(name != user_name){
                QList<QListWidgetItem *> _sender = ui->users->findItems(name, Qt::MatchExactly);
                if (_sender.isEmpty()){
                    ui->users->addItem(name);
                    QByteArray buffer = encodeMessage(user_name, START_CHAT);
                    socket->writeDatagram(buffer, QHostAddress::Broadcast, _port);
                }
            }
        }
        else if (message == END_CHAT){
            for (int i = 0; i < ui->users->count(); i++){
                if (ui->users->item(i)->text() == name){
                    ui->users->takeItem(i);
                }
            }
        }
        else showMessage(name, message);
    }
    if (isNew){
        ui->users->sortItems(Qt::AscendingOrder);
        isNew = false;
    }
}

void ChatWidget::showMessage(const QString& name, const QString& message){
    QTime time = QTime::currentTime();
    QString line = QString("<font color=\"%1\">[%2] <b>%3</b>:</font> %4")
            .arg(name == user_name ? "red" : "blue")
            .arg(time.toString()).arg(name).arg(message);
    ui->textEdit->append(line);
}
