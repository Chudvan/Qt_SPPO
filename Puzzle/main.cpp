#include <QApplication>
#include "configurationdialog.h"
#include <QDebug>
#include <QGraphicsView>
#include <puzzlepiece.h>
#include <gamelogic.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationDialog c;
    c.show();
    return a.exec();
}
