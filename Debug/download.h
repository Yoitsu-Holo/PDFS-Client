#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFile>
#include <QTcpSocket>
#include <QQueue>
#include <cstdio>

#include "protocol.h"

class Download : public QObject
{
    Q_OBJECT
private:
    size_t cnt;
    char sha[64];
    QFile *downloadFile;
    QTcpSocket *downloadSocket;
    QQueue<QPair<QString,QString>> serverTable;

public:
    Download(QFile * DownloadFile,QByteArray RawMsg);
    ~Download();

private slots:
    void on_ServerConnected();
    void on_ServerReturned();

private:
    void ServerConnect();
};

#endif // DOWNLOAD_H
