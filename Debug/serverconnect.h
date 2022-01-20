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
    void ConnectServer(QString host,unsigned short port);
    void SendMsg(QByteArray msg);
    void SendMsg(QByteArray msg,size_t len);
    void Close();
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
