#include "gserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec* rus = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(rus);
    //
    QApplication a(argc, argv);
    gserver w;
    w.show();

    return a.exec();
}
