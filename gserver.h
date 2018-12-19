#ifndef GSERVER_H
#define GSERVER_H
//
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
//
#include "msock.h"

namespace Ui {
class gserver;
}

class gserver : public QMainWindow
{
    Q_OBJECT

public:
    explicit gserver(QWidget *parent = 0);
    ~gserver();

private slots:
    void climon();
    void cliconnect();
    void clidisconn();
    //
    void log(QString s);
    //
private:
    //
    Ui::gserver *ui;
    //
    int conn_lim;
    QTcpServer *listener;
    QList<msock*> st;    // Client states
};

#endif // GSERVER_H
