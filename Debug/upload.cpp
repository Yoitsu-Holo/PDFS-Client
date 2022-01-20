#include "upload.h"

UpLoad::UpLoad(QString ServerHost,int ServerPort,QFile *file,QString Path,Header *header)
{
    UploadSocket=new QTcpSocket();
    UploadSocket->connectToHost(ServerHost,ServerPort);
    UploadFile=file;
    FilePath=Path;
    FileName=UploadFile->fileName().split('/').back();
    tcpHeader=header;

    //建立型号与槽
    connect(UploadSocket,&QTcpSocket::connected,this,&UpLoad::on_ServerConnected);
    connect(UploadSocket,&QTcpSocket::disconnected,this,&UpLoad::on_ServerConnectionLose);
    connect(this,&UpLoad::ServerConnected,this,&UpLoad::on_SendHeader);
    connect(UploadSocket,&QTcpSocket::readyRead,this,&UpLoad::on_ServerReturned);
}

UpLoad::~UpLoad()
{
}

void UpLoad::on_ServerConnected()
{
    emit this->ServerConnected();
}

void UpLoad::on_ServerConnectionLose()
{
    emit this->ServerConnectionLose();
}

void UpLoad::on_SendHeader()
{
    //发送头
    QByteArray header;
    tcpHeader->set_op(opCode_SendFile);
    header.append(tcpHeader->get_KeyHeader());
    header.append(char(0)).append(char(FilePath.length()));
    header.append(FilePath.toLatin1());
    //header.append(FileName.length());
    header.append(FileName.toUtf8());
    UploadSocket->write(header);
}

void UpLoad::on_SendFile()
{
    //发送文件
    FileSize=UploadFile->size();//文件大小
    int len;
    qDebug("文件发送开始");
    do{
        memset(buf,0x0,sizeof(buf));
        len=0;
        len=UploadFile->read(buf,sizeof(buf));
        sendSize+=len;
        UploadSocket->write(buf,len);
    }while(len>0);
    UploadFile->close();
    UploadSocket->disconnectFromHost();
    UploadSocket->close();
    qDebug("文件发送完成");
    emit this->FileSendFinish();
    this->~UpLoad();
}

void UpLoad::on_ServerReturned()
{
    QByteArray serverReturn=UploadSocket->readAll();
    qDebug()<<serverReturn.toHex();
    if(serverReturn[0]==char(255))
        on_SendFile();
}
