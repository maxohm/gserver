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
                QHostAddress(stif),
                stport)){
        log("gserver::gserver listener listening on port "+QString::number(stport));
        log("gserver::gserver listener->maxPendingConnections() = "+QString::number(conn_lim));
        //
        this->setWindowTitle("GSERVER "+stif+":"+QString::number(stport));
    } else {
        log("gserver::gserver failed to setup listener on port "+QString::number(stport));
    };
    //
    msock* s = new msock();
    //connect(s->ticker, SIGNAL(timeout()), this, SLOT(climon()));
    connect(listener, SIGNAL(newConnection()), this, SLOT(cliconnect()));
    //
    connect(this->ui->log->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this->ui->log, SLOT(scrollToBottom()));
}

gserver::~gserver()
{
    delete ui;
}


void  gserver::tx(QString s)
{
}

void  gserver::rx()
{
}

void gserver::monitor()
{
    log("gserver::climon()");
}


void gserver::cliconnect()
{
    int id = st.count();
    if (conn_lim<=id) return;
    id++;
    //
    msock* s = new msock();
    s->state.replace(
                QString::number(stport),
                QString::number(stport+id)
                );
    //
    QStringList* h = new QStringList(
                s->state.split("|")
                );
    //
    QString _st = pdesc.value(
                h->at(2).toInt()
                );
    if (_st.isEmpty() || _st.isNull())
        return;
    //
    //log("gserver::cliconnect() id "+h->at(1));
    log("Новый клиент ID ["+h->at(1)+"] состояние ["+_st+"]");
    //
    s->sock = listener->nextPendingConnection();
    s->sock->waitForConnected();
    s->tx(s->state);
    connect(s->sock,SIGNAL(readyRead()),s,SLOT(stmod()));
    //
    st.append(s);
    conn_lim--;
}

void gserver::clidisconn()
{
    log("gserver::clidisconn() id ");
}

void gserver::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();
    //
    int rc = ui->log->rowCount();
    //
    ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    ui->log->setItem(rc,0,t);
    ui->log->resizeColumnsToContents();
}
