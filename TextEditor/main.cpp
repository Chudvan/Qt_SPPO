#include "mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationVersion(APPLICATION_VERSION);
    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);
    a.setWindowIcon(QIcon(":/icons/images/new.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
