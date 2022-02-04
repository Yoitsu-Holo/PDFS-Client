#include "download.h"

Download::Download(QFile *DownloadFile,QByteArray RawMsg)
{
    qDebug("RMSG: %s",qPrintable(RawMsg.toHex()));
    for(int i=0;i<64;i++)
        sha[i]=RawMsg.at(i);
    RawMsg.remove(0,64);
    downloadFile=DownloadFile;
    //downloadFile->open(QIODevice::ReadWrite);
    downloadSocket=new QTcpSocket();
    int pos=0;
    cnt=0;
    QByteArray info;
    QByteArray lenth=RawMsg.mid(0,8);
    qDebug("长度: %s",qPrintable(lenth.toHex()));
    RawMsg.remove(0,8);
    while(RawMsg.size())
    {
        size_t len=RawMsg.at(pos);
        info = RawMsg.mid(pos+1,pos+len);
        qDebug("mid: %d %lld %s",pos+1,len,qPrintable(info));
        serverTable.push_back({info.split(':').at(0),info.split(':').at(1)});
        RawMsg.remove(0,len+1);
    }
    connect(downloadSocket,&QTcpSocket::connected,this,&Download::on_ServerConnected);
    connect(downloadSocket,&QTcpSocket::readyRead,this,&Download::on_ServerReturned);
    connect(downloadSocket,&QTcpSocket::disconnected,this,&Download::on_ServerLose);
    ServerConnect();
}

Download::~Download()
{
    downloadFile->close();
}

void Download::on_ServerReturned()
{
    QByteArray serverReturn = downloadSocket->readAll();
    //qDebug("%s",qPrintable(serverReturn.toHex()));
    downloadFile->write(serverReturn);
    qDebug("Done!");
}

void Download::ServerConnect()
{
    if(!serverTable.empty())
    {
        downloadSocket->connectToHost(serverTable.front().first,serverTable.front().second.toInt());
        qDebug("try to connect: %s::%d",qPrintable(serverTable.front().first),serverTable.front().second.toInt());
    }
    else
        this->~Download();
}

void Download::on_ServerConnected()
{
    qDebug("Connect!");
    cnt++;
    QByteArray header;
    std::stringstream ss;
    ss<<cnt-1;
    header.append(char(2));
    header.append(sha,64).append(char('-')).append(ss.str());
    qDebug("send:: %s",qPrintable(header));
    downloadSocket->write(header);
}

void Download::on_ServerLose()
{
    serverTable.pop_front();
    this->ServerConnect();
}
