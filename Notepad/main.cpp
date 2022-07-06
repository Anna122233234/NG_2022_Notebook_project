#include "notepad.h"

#include <QApplication>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad w;
    w.show();
    return a.exec();
}
