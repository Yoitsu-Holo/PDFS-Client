#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QFile>


class UpLoad : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *UploadSocket;//上传的socket
    QTimer Timer;           //计时器
    QFile *UploadFile;       //上传的文件
    QDataStream FileStream; //文件数据流
    size_t FileSize;        //文件大小
    char buf[4096];         //文件缓冲区 4K

public:
    UpLoad(QString ServerHost,int ip,QFile *file);
    void send();
public slots:
//    void on_ServerConnected();
//    void on_SendFile();
//    void on_ServerConnectLose();

signals:
    void ServerConnectLose();
};

#endif // UPLOAD_H
