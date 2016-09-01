#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(new FileRecordManager("record.dat"));
    w.show();

    return a.exec();
}
