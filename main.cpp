#include "gserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gserver w;
    w.show();

    return a.exec();
}
