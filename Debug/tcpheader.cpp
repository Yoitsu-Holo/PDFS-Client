#include "tcpheader.h"

Header::Header()
{
    this->op = 0;
    this->header.clear();
    this->password.clear();
    this->userName.clear();
    this->key.clear();
    key.resize(20);
}

void Header::set_op(int Op)
{
    op=Op;
}

void Header::set_UserName(QString UserName)
{
    userName=UserName;
}

void Header::set_Password(QString Password)
{
    password=Password;
}

void Header::set_Key(QByteArray Key)
{
    if(Key.length()==20)
        key=Key;
}

QByteArray Header::get_UserHeader()
{
    rebuildUserHeader();
    return header;
}

QByteArray Header::get_KeyHeader()
{
    rebuildKeyHeader();
    return header;
}

QByteArray Header::get_DelHeader()
{
    rebuildDelHeader();
    return header;
}

void Header::rebuildKeyHeader()
{
    qDebug("rebuild key");
    header.clear();
    header.append(op);
    header.append(key);
}

void Header::rebuildUserHeader()
{
    qDebug("rebuild user");

    header.clear();
    header.append(op);
    header.append(userName.toLatin1());

    while(header.size()<=opPart_1)
        header.append(char(0));
    header.append(password.toLatin1());
    while(header.size()<=opPart_2)
        header.append(char(0));
}

void Header::rebuildDelHeader()
{
    qDebug("rebuild del");
    header.clear();
    header.append(op);
    header.append(key);
    header.append(password.toLatin1());
    while(header.length()<=opPart_2)
        header.append(char(0));
}
