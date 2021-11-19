#include "chatwidget.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDataStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption name_param(QStringList({"n", "name"}), "name", "name");
    QCommandLineOption port_param(QStringList({"p", "port"}), "port", "port");
    parser.addOption(name_param);
    parser.addOption(port_param);
    parser.process(a);
    QString username, port;
    username = parser.value(name_param);
    port = parser.value(port_param);
    if (username.isEmpty())username = "User1";
    if (port.isEmpty())port = "2734";


    ChatWidget w(username, port.toUInt());
    w.show();
    return a.exec();
}
