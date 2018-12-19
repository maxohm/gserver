#include "gserver.h"
#include "ui_gserver.h"
//
#include <QDateTime>

gserver::gserver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gserver)
{
    ui->setupUi(this);
    //
    listener = new QTcpServer(this);
    conn_lim = listener->maxPendingConnections();
    //
    if (listener->listen(
                QHostAddress("127.0.0.1"),
                stport)){
        log("gserver::gserver listener listening on port "+QString::number(stport));
        log("gserver::gserver listener->maxPendingConnections() = "+QString::number(conn_lim));
    } else {
        log("gserver::gserver failed to setup listener on port "+QString::number(stport));
    };


    msock* s = new msock();
    connect(s->ticker, SIGNAL(timeout()), this, SLOT(climon()));
    connect(listener, SIGNAL(newConnection()), this, SLOT(cliconnect()));
}

gserver::~gserver()
{
    delete ui;
}


void gserver::climon()
{
    log("gserver::climon() id ");
//    for (int i=1; i<=conn_lim; i++){
//        QStringList* h = new QStringList(
//                    st[i]->state.split("|")
//                    );
//        if (h->size()>2) log("gserver::climon() id "+h->at(2));
//    };
}


void gserver::cliconnect()
{
    int id = st.count();


    if (conn_lim>id){
        id++;
        msock* s = new msock(id);
        st.append(s);
        //
        QStringList* h = new QStringList(
                          s->state.split("|")
                          );
        log("gserver::cliconnect() id "+h->at(1));
    };

    //for (int i=0; i<st.count(); i++){


//        if ( NULL==s.) {
//          log("gserver::climon() id "+QString::number(i));
//          return;
//        };
//        QStringList* h = new QStringList(
//                    st[i]->state.split("|")
//                    );
//        if (h->size()<3) {
//            st[i]->sock = listener->nextPendingConnection();
//
//        }
    //};

}

void gserver::clidisconn()
{
    log("gserver::clidisconn() id ");
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
