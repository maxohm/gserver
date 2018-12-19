#ifndef GSERVER_H
#define GSERVER_H

#include <QMainWindow>

#ifdef HAVE_QT5
#include <QTcpSocket>
static const QStringList sstate  = QStringList() << "QAbstractSocket::UnconnectedState" << "QAbstractSocket::HostLookupState" << "QAbstractSocket::ConnectingState" << "QAbstractSocket::ConnectedState" << "QAbstractSocket::BoundState" << "QAbstractSocket::ClosingState" << "QAbstractSocket::ListeningState";
static const int stport = 2000;
#endif

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
    //void slotConnected();
    void log(QString s);
    //
private:
    //

    Ui::gserver *ui;
    //
#ifdef HAVE_QT5
    QMap<int, QString>      c_state;    // Client states
    QMap<int, QTcpSocket*>  c_sock;     // Client socks
    QMap<int, QTimer*>      c_timer;    // Client timers
#endif

};

#endif // GSERVER_H
