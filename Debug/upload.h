#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QFile>
#include <QTextcodec>

#include "protocol.h"
#include "tcpheader.h"

class UpLoad : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *UploadSocket;//上传的socket
    //QTimer Timer;           //计时器
    QFile *UploadFile;       //上传的文件
    char buf[4*1024];       //文件缓冲区 4K
    size_t sendSize=0;      //已发送文件大小
    size_t FileSize;        //文件大小
    QString FilePath;       //目标文件路径
    QString FileName;
    Header *tcpHeader;

public:
    UpLoad(QString ServerHost,int ServerPort,QFile *file,QString Path,Header *header);
    ~UpLoad();

public slots:
    void on_ServerConnected();
    void on_SendHeader();
    void on_SendFile();
    void on_ServerConnectionLose();
    void on_ServerReturned();

signals:
    void ServerConnectionLose();
    void ServerConnected();
    void FileSendFinish();
    void Error();
};

#endif // UPLOAD_H
