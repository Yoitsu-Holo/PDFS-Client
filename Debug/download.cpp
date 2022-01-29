#include "download.h"

Download::Download(QFile *DownloadFile,QByteArray RawMsg)
{
    qDebug("RMSG: %s",qPrintable(RawMsg.toHex()));
    for(int i=0;i<40;i++)
        sha[i]=RawMsg.at(i);
    RawMsg.remove(0,40);
    downloadFile=DownloadFile;
    downloadSocket=new QTcpSocket();
    int pos=0;
    cnt=0;
    QByteArray info;
    RawMsg.remove(0,1);
    qDebug("fuck:%lld",RawMsg.length());
    while(pos<RawMsg.length())
    {
        size_t len=RawMsg.at(pos);
        info = RawMsg.mid(pos+1,pos+len);
        qDebug("%d %lld %s",pos+1,len,qPrintable(info));
        serverTable.push_back({info.split(':').at(0),info.split(':').at(1)});
        pos+=len+1;
    }
    ServerConnect();
}

Download::~Download()
{

}

void Download::on_ServerReturned()
{
    downloadFile->write(downloadSocket->readAll());
    serverTable.pop_front();
    this->ServerConnect();
    qDebug("Done!");
}

void Download::ServerConnect()
{
    if(!serverTable.empty())
    {
        downloadSocket->connectToHost(serverTable.front().first,serverTable.front().second.toInt());
        qDebug("Connect!");
        connect(downloadSocket,&QTcpSocket::connected,this,&Download::on_ServerConnected);
        connect(downloadSocket,&QTcpSocket::readyRead,this,&Download::on_ServerReturned);
        qDebug("%s::%d",qPrintable(serverTable.front().first),serverTable.front().second.toInt());
    }
    else
        this->~Download();
}

void Download::on_ServerConnected()
{
    qDebug("Send!");
    cnt++;
    QByteArray header;
    std::stringstream ss;
    ss<<cnt;
    header.append(opCode_DownloadFile).append(sha).append(char('-')).append(QString().fromStdString(ss.str()).toLatin1());
    downloadSocket->write(header);
    disconnect(downloadSocket);
}
