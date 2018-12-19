#include "gserver.h"
#include "ui_gserver.h"
//
#include <QDate>
#include <QTimer>
#include <QTcpServer>

gserver::gserver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gserver)
{
    ui->setupUi(this);
    //
    QTcpServer *listener = new QTcpServer(this);
    if (listener->listen(
                QHostAddress("127.0.0.1"),
                stport)){
        log("gserver::gserver listener listening on port "+QString::number(stport));
    } else {
        log("gserver::gserver failed to setup listener on port "+QString::number(stport));
    };
}

gserver::~gserver()
{
    delete ui;
}

void gserver::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();

    int rc = ui->log->rowCount();

    ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    ui->log->setItem(rc,0,t);
    ui->log->resizeColumnsToContents();
}
