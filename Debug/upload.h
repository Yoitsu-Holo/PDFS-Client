#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>


class UpLoad : public QObject
{
    Q_OBJECT
    QTcpSocket *uploadSocket;
    QTimer timer;
public:
    UpLoad();

signals:

};

#endif // UPLOAD_H
