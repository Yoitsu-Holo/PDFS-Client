#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H

#include <QObject>
#include <QString>
#include <QHostInfo>
#include <QTcpSocket>

class ServerConnect:public QObject
{
    Q_OBJECT
private:
    QTcpSocket *tcpClient;
    QByteArray ServerReturnedMsg;

public:
    ServerConnect();
    QString ConnectTest(QString host);
    void ConnectServer(QString host,QString port);
    void SendMsg(QByteArray msg);
    QByteArray GetServerMsg();

public slots:
    void onConnected();
    void onDisconnected();
    void onSocketReadyRead();

signals:
    void serverReady();
    void serverLose();
    void serverReturned();
};

#endif // SERVERCONNECT_H
