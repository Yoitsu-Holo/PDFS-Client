#ifndef PDFS_CLIENT_H
#define PDFS_CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTreeWidgetItem>
#include <QDir>
#include <QList>

#include "PDFSFileSystem.cpp"
#include "serverconnect.h"
#include "loginheader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PDFS_Client; }
QT_END_NAMESPACE

class PDFS_Client : public QMainWindow
{
    Q_OBJECT

private:
    QTcpSocket *Client;
    LoginHeader tcpHeader;
    PDFS_FileSystem *fileSystemModel;

public:
    PDFS_Client(QWidget *parent = nullptr);
    ~PDFS_Client();

    void refreshFileTree();

private slots:
    void on_ServerConnect_clicked();
    void on_Login_clicked();
    void on_FileTree_itemClicked(QTreeWidgetItem *item, int column);
    void on_FileTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::PDFS_Client *ui;
};
#endif // PDFS_CLIENT_H
