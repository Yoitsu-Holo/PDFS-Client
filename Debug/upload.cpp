#include "upload.h"

Upload::Upload(QString ServerHost,int ServerPort,QFile *file,QString Path,Header *header)
{
    UploadSocket=new QTcpSocket();
    UploadSocket->connectToHost(ServerHost,ServerPort);
    UploadFile=file;
    FileName=UploadFile->fileName().split('/').back();
    FilePath=Path+FileName;
    tcpHeader=header;
    bufSize=64*1024;

    //建立型号与槽
    connect(UploadSocket,&QTcpSocket::connected,this,&Upload::on_ServerConnected);
    connect(UploadSocket,&QTcpSocket::disconnected,this,&Upload::on_ServerConnectionLose);
    connect(this,&Upload::ServerConnected,this,&Upload::on_SendHeader);
    connect(UploadSocket,&QTcpSocket::readyRead,this,&Upload::on_ServerReturned);
}

Upload::~Upload()
{
}

void Upload::on_ServerConnected()
{
    emit this->ServerConnected();
}

void Upload::on_ServerConnectionLose()
{
    emit this->ServerConnectionLose();
}

void Upload::on_SendHeader()
{
    //发送头
    QByteArray header;
    tcpHeader->set_op(opCode_SendFile);
    header.append(tcpHeader->get_KeyHeader());
    header.append(FilePath.toLatin1());
    qDebug("Path: %s",qPrintable(FilePath));
    UploadSocket->write(header);
}

void Upload::on_SendSize(qint64 sentSize)
{
    m_SentSize-=sentSize;
    emit proccess((int)((m_FileSize-m_SentSize)*100/m_FileSize));
    qDebug()<<"sned:"<<sentSize <<" | last: "<<m_SentSize;
    if(m_SentSize)
    {
        //发送文件
        qDebug("文件发送64K");
        outBlock=UploadFile->read(qMin(m_SentSize,bufSize));
        UploadSocket->write(outBlock);
        outBlock.resize(0);
    }
    else //文件发送结束
    {
        UploadFile->close();
        UploadSocket->disconnectFromHost();
        UploadSocket->close();
        qDebug("文件发送完成");
        emit this->FileSendFinish();
        this->~Upload();
    }
}

void Upload::on_ServerReturned()
{
    QByteArray serverReturn=UploadSocket->readAll();
    qDebug()<<"server return : "<<serverReturn.toHex();
    if(serverReturn[0]==char(255))
    {
        m_SentSize=m_FileSize=UploadFile->size();
        connect(UploadSocket,&QTcpSocket::bytesWritten,this,&Upload::on_SendSize);
        QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
        sendOut.setVersion(QDataStream::Qt_6_2);
        on_SendSize(0);
    }
}
