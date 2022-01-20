#include "upload.h"

UpLoad::UpLoad(QString ServerHost,int port,QFile *file)
{
    UploadSocket=new QTcpSocket();
    UploadFile=file;
    //connect(UploadSocket,QTcpSocket::connected,this,this::on_ServerConnected);
}
