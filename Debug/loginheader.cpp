#include "loginheader.h"

LoginHeader::LoginHeader()
{
    this->op = 0;
    this->header.clear();
    this->password.clear();
    this->userName.clear();
    this->headerReady = false;
    memset(key,0x0,sizeof(key));
}

void LoginHeader::set_op(int Op)
{
    op=Op;
    headerReady = false;
}

void LoginHeader::set_UserName(QString UserName)
{
    userName=UserName;
    headerReady = false;
}

void LoginHeader::set_Password(QString Password)
{
    password=Password;
    headerReady = false;
}

QByteArray LoginHeader::get_Header()
{
    if(!headerReady)
    {
        rebuildLoginHeader();
        headerReady=true;
    }
    return header;
}

QString LoginHeader::get_RawHeader()
{
    if(!headerReady)
    {
        rebuildLoginHeader();
        headerReady=true;
    }
    return rawHeader;
}

void LoginHeader::rebuildKeyHeader()
{
    rawHeader.clear();
    rawHeader.append(op);
    for(int i=0;i<keyLength;i++)
        rawHeader.append(key[i]);
    rawHeader.append(key);
    header = rawHeader.toLatin1();
}

void LoginHeader::rebuildLoginHeader()
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
