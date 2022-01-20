#include "serverconnect.h"

ServerConnect::ServerConnect()
{
    tcpClient=new QTcpSocket();
    connect(tcpClient,&QTcpSocket::connected,this,&ServerConnect::onConnected);
    connect(tcpClient,&QTcpSocket::disconnected,this,&ServerConnect::onDisconnected);
    connect(tcpClient,&QTcpSocket::readyRead,this,&ServerConnect::onSocketReadyRead);
}

QString ServerConnect::ConnectTest(QString host)
{
    return host;
}

void ServerConnect::ConnectServer(QString host,unsigned short port)
{
    tcpClient->connectToHost(host,port);
    qDebug("try to connect::%s:%d",qPrintable(host),port);
}

void ServerConnect::SendMsg(QByteArray msg)
{
    //msg.append("\n");
    qDebug("msg sended");
    tcpClient->write(msg);
}

void ServerConnect::SendMsg(QByteArray msg,size_t len)
{
    //msg.append("\n");
    qDebug("msg sended");
    tcpClient->write(msg,len);
}

QByteArray ServerConnect::GetServerMsg()
{
    return ServerReturnedMsg;
}

void ServerConnect::Close()
{
    tcpClient->disconnectFromHost();
    tcpClient->close();
}

void ServerConnect::onConnected()
{
    qDebug("connect already");
    emit serverReady();
}

void ServerConnect::onDisconnected()
{
    qDebug("connect lose");
    emit serverLose();
}

void ServerConnect::onSocketReadyRead()
{
    qDebug("server Ready");
    ServerReturnedMsg.clear();
    ServerReturnedMsg = tcpClient->readAll();
    emit serverReturned();
}
