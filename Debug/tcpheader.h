#ifndef TCPHEADER_H
#define TCPHEADER_H

#include <QString>
#include <QBitArray>

#include "protocol.h"

class Header
{
public:
    Header();

private:
    char op;
    QByteArray key;
    QString userName;
    QString password;
    QString extend;
    QByteArray header;
    bool userHeaderReady;
    bool keyHeaderReady;
    bool delHeaderReady;

public:
    void set_op(int Op);
    void set_UserName(QString UserName);
    void set_Password(QString Password);
    void set_Key(QByteArray Key);
    QByteArray get_UserHeader();
    QByteArray get_KeyHeader();
    QByteArray get_DelHeader();

private:
    void rebuildKeyHeader();
    void rebuildUserHeader();
    void rebuildDelHeader();
};

#endif // TCPHEADER_H
