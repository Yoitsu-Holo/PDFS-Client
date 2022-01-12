#include "tcpheader.h"

Header::Header()
{
    this->op = 0;
    this->header.clear();
    this->password.clear();
    this->userName.clear();
    this->key.clear();
    this->userHeaderReady=false;
    this->keyHeaderReady=false;
    this->delHeaderReady=false;
    key.resize(20);
}

void Header::set_op(int Op)
{
    userHeaderReady=keyHeaderReady=delHeaderReady=false;
    op=Op;
}

void Header::set_UserName(QString UserName)
{
    userHeaderReady=delHeaderReady=false;
    userName=UserName;
}

void Header::set_Password(QString Password)
{
    userHeaderReady=delHeaderReady=false;
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
    if(!keyHeaderReady)
    {
        qDebug("rebuild key");

        userHeaderReady=false;
        keyHeaderReady=true;
        delHeaderReady=false;

        header.clear();
        header.append(op);
        for(auto &&keyEle:key)
            header.append(keyEle);
        header.append(key);
    }
}

void Header::rebuildUserHeader()
{
    if(!userHeaderReady)
    {
        qDebug("rebuild user");

        userHeaderReady=true;
        keyHeaderReady=false;
        delHeaderReady=false;

        header.clear();
        header.append(op);
        header.append(userName.toLatin1());

        while(header.size()<=opPart_1)
            header.append(char(0));
        header.append(password.toLatin1());
        while(header.size()<=opPart_2)
            header.append(char(0));
    }
}

void Header::rebuildDelHeader()
{
    if(!delHeaderReady)
    {
        qDebug("rebuild del");
        userHeaderReady=false;
        keyHeaderReady=false;
        delHeaderReady=true;

        header.clear();
        header.append(op);
        header.append(key);
        header.append(password.toLatin1());
        while(header.length()<=opPart_2)
            header.append(char(0));
    }
}
