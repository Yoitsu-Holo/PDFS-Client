#include "tcpheader.h"

Header::Header()
{
    this->op = 0;
    this->header.clear();
    this->password.clear();
    this->userName.clear();
    this->userHeaderReady=false;
    this->keyHeaderReady=false;
    memset(key,0x0,sizeof(key));
}

void Header::set_op(int Op)
{
    userHeaderReady=keyHeaderReady=false;
    op=Op;
}

void Header::set_UserName(QString UserName)
{
    userHeaderReady=false;
    userName=UserName;
}

void Header::set_Password(QString Password)
{
    userHeaderReady=false;
    password=Password;
}

QByteArray Header::get_UserHeader()
{
    if(!userHeaderReady)
    {
        userHeaderReady=true;
        keyHeaderReady=false;
        rebuildUserHeader();
    }
    return header;
}

QByteArray Header::get_KeyHeader()
{
    if(!keyHeaderReady)
    {
        userHeaderReady=false;
        keyHeaderReady=true;
        rebuildKeyHeader();
    }
    return header;
}

QString Header::get_RawUserHeader()
{
    rebuildUserHeader();
    return rawHeader;
}

QString Header::get_RawKeyHeader()
{
    rebuildKeyHeader();
    return rawHeader;
}

void Header::rebuildKeyHeader()
{
    rawHeader.clear();
    rawHeader.append(op);
    for(int i=0;i<keyLength;i++)
        rawHeader.append(key[i]);
    rawHeader.append(key);
    header = rawHeader.toLatin1();
}

void Header::rebuildUserHeader()
{
    rawHeader.clear();
    rawHeader.append(op);
    rawHeader.append(userName);

    while(rawHeader.size()<=username_end)
        rawHeader.push_back(QChar(0));
    rawHeader.append(password);
    while(rawHeader.size()<=password_end)
        rawHeader.push_back(QChar(0));
    header = rawHeader.toLatin1();
}
