#ifndef PDFS_CLIENT_H
#define PDFS_CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTreeWidgetItem>
#include <QDir>
#include <QList>
#include <QMessageBox>
#include <QTextcodec>

#include <istream>
#include <ostream>
#include <string>

#include "PDFSFileSystem.cpp"
#include "serverconnect.h"
#include "tcpheader.h"
#include "upload.h"
#include "download.h"

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
    Upload *uploadSocket;
    QFile *tempFile;

public:
    PDFS_Client(QWidget *parent = nullptr);
    ~PDFS_Client();
    void RefreshFileTree();
    void RequestFileTree(QString Path);
    void BuildFileTree(QByteArray dirInfo);

private slots:
    void onServerReturned();
    void on_ServerConnect_clicked();
    void on_Login_clicked();
    void on_FileTree_itemClicked(QTreeWidgetItem *item, int column);
    void on_FileTree_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_Register_clicked();
    void on_DeleteUser_clicked();
    void on_UpLoad_clicked();
    void on_Download_clicked();

    void on_DebugSend_clicked();

private:
    Ui::PDFS_Client *ui;
};
#endif // PDFS_CLIENT_H
