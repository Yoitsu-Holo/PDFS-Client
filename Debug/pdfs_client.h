#ifndef PDFS_CLIENT_H
#define PDFS_CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTreeWidgetItem>
#include <QDir>
#include <QList>

#include "PDFSFileSystem.cpp"
#include "serverconnect.h"
#include "tcpheader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PDFS_Client; }
QT_END_NAMESPACE

class PDFS_Client : public QMainWindow
{
    Q_OBJECT

private:
    ServerConnect *server;
    PDFS_FileSystem *fileSystemModel;
    Header *tcpHeader;
    QByteArray Key;

public:
    PDFS_Client(QWidget *parent = nullptr);
    ~PDFS_Client();
    void SendUserMsg();
    void SendNomalMsg();
    void SendDelMsg();
    void RefreshFileTree();

private slots:
    void onServerReturned();
    void on_ServerConnect_clicked();
    void on_Login_clicked();
    void on_FileTree_itemClicked(QTreeWidgetItem *item, int column);
    void on_FileTree_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_Register_clicked();

    void on_DeleteUser_clicked();

private:
    Ui::PDFS_Client *ui;
};
#endif // PDFS_CLIENT_H
