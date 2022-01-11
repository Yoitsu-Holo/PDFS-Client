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
    char key[keyLength];
    QString userName;
    QString password;
    QString extend;
    QByteArray header;
    QString rawHeader;
    bool keyHeaderReady;
    bool userHeaderReady;

public:
    void set_op(int Op);
    void set_UserName(QString UserName);
    void set_Password( QString Password);
    QByteArray get_UserHeader();
    QByteArray get_KeyHeader();
    QString get_RawUserHeader();
    QString get_RawKeyHeader();

private:
    void rebuildKeyHeader();
    void rebuildUserHeader();
};

#endif // TCPHEADER_H
