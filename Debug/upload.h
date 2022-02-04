#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QFile>
#include <QTextcodec>
#include <QtAlgorithms>

#include "protocol.h"
#include "tcpheader.h"

class Upload : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *UploadSocket;//上传的socket
    QFile *UploadFile;      //上传的文件
    qint64 bufSize;         //文件缓冲区 4K
    qint64 m_SentSize;        //文件大小
    qint64 m_FileSize;
    QByteArray outBlock;
    QString FilePath;       //目标文件路径
    QString FileName;
    Header *tcpHeader;

public:
    Upload(QString ServerHost,int ServerPort,QFile *file,QString Path,Header *header);
    ~Upload();

public slots:
    void on_ServerConnected();
    void on_SendHeader();
    void on_ServerConnectionLose();
    void on_ServerReturned();
    void on_SendSize(qint64 sendSize);


signals:
    void ServerConnectionLose();
    void ServerConnected();
    void FileSendFinish();
    void Error();
    void proccess(int pro);
};

#endif // UPLOAD_H
