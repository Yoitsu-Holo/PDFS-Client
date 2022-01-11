#include "pdfs_client.h"
#include "ui_pdfs_client.h"

PDFS_Client::PDFS_Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PDFS_Client)
{
    ui->setupUi(this);
    fileSystemModel=new PDFS_FileSystem();
    server=new ServerConnect();

    ui->ServerHost->setText("1.117.64.144");
    ui->ServerPort->setText("9999");

//    ui->FileTree->setColumnCount(3);
//    //ui->FileTree->setColumnHidden(0,true);
//    QList<QString> headerName;
//    headerName.append("FileName");
//    headerName.append("FileType");
//    headerName.append("FileSize");
//    ui->FileTree->setHeaderLabels(headerName);

//    fileSystemModel->TEST();
//    RefreshFileTree();
    connect(server,SIGNAL(serverReturned()),this,SLOT(onServerReturned()));
}

PDFS_Client::~PDFS_Client()
{
    delete ui;
}

void PDFS_Client::SendUserMsg()
{
    tcpHeader.set_UserName(ui->UserName->text());
    tcpHeader.set_Password(ui->Password->text());
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader.get_UserHeader().toHex()+"\n");
    server->SendMsg(tcpHeader.get_UserHeader());
}

void PDFS_Client::SendNomalMsg()
{
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader.get_UserHeader().toHex()+"\n");
    server->SendMsg(tcpHeader.get_KeyHeader());
}

void PDFS_Client::RefreshFileTree()
{
    QList<QTreeWidgetItem *> items;
    QList<QStringList> fileStruct = fileSystemModel->CtoQ_FileTree(fileSystemModel->getFileTree());
    for (auto && fileEle:fileStruct)
        items.append(new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), fileEle));
    ui->FileTree->clear();
    ui->FileTree->insertTopLevelItems(0,items);
}

void PDFS_Client::onServerReturned()
{
    auto serverReturn = server->GetServerMsg();
    ui->DebugInfo->append("[in]:" + serverReturn.toHex() +"\n");
}

void PDFS_Client::on_ServerConnect_clicked()
{
    ui->DebugInfo->append("Try to connect server");
    server->ConnectServer(ui->SHost->text(),ui->SPort->text());
}

void PDFS_Client::on_Login_clicked()
{
    tcpHeader.set_op(opCode_Login);
    SendUserMsg();
}

void PDFS_Client::on_Register_clicked()
{
    tcpHeader.set_op(opCode_CreateUser);
    SendUserMsg();
}

void PDFS_Client::on_FileTree_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->DebugInfo->append("user clicked dir:    " + item->data(0,0).toString());
}

void PDFS_Client::on_FileTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->DebugInfo->append("user double clicked dir:    " + item->data(0,0).toString());

    if(item->data(1,0).toString()=="<DIR>")
        fileSystemModel->inPath(item->data(0,0).toString());
    if(item->data(1,0).toString()=="<PRE>")
        fileSystemModel->outPath();
    ui->DLPath->setText(fileSystemModel->getPath());
    RefreshFileTree();
}
