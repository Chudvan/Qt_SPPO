#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QTime>
#define START_CHAT "START_CHAT"
#define END_CHAT "END_CHAT"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatWidget; }
QT_END_NAMESPACE

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(QString name, quint16 port, QWidget *parent = nullptr);
    ~ChatWidget();
    QByteArray encodeMessage(const QString &name, const QString &message);
    QPair<QString, QString> decodeMessage(QByteArray& data);
    void showMessage(const QString& name, const QString& message);
public slots:
    void sendMessage();
    void readPendingDatagrams();

private:
    Ui::ChatWidget *ui;
    QUdpSocket *socket;
    QString user_name;
    quint16 _port;
    bool isNew;
};
#endif // CHATWIDGET_H
