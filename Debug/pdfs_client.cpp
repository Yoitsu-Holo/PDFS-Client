#include "pdfs_client.h"
#include "ui_pdfs_client.h"

PDFS_Client::PDFS_Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PDFS_Client)
{
    ui->setupUi(this);
    fileSystemModel=new PDFS_FileSystem();
    tcpHeader = new Header();
    server=new ServerConnect();

//    ui->ServerHost->setText("1.117.64.144");
    ui->ServerHost->setText("43.154.178.243");
    ui->ServerPort->setText("9999");
    ui->UserName->setText("YoitsuHolo");
    ui->Password->setText("YoitsuHolo");
    ui->FileTree->setColumnCount(3);
    //ui->FileTree->setColumnHidden(0,true);
    QList<QString> headerName;
    headerName.append("FileName");
    headerName.append("FileType");
    headerName.append("FileSize");
    ui->FileTree->setHeaderLabels(headerName);

    //fileSystemModel->TEST();
    RefreshFileTree();
    connect(server,SIGNAL(serverReturned()),this,SLOT(onServerReturned()));
}

PDFS_Client::~PDFS_Client()
{
    delete ui;
}

void PDFS_Client::SendUserMsg()
{
    tcpHeader->set_UserName(ui->UserName->text());
    tcpHeader->set_Password(ui->Password->text());
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader->get_UserHeader().toHex()+"\n");
    server->SendMsg(tcpHeader->get_UserHeader());
}

void PDFS_Client::SendNomalMsg()
{
    tcpHeader->set_Key(Key);
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader->get_KeyHeader().toHex()+"\n");
    server->SendMsg(tcpHeader->get_KeyHeader());
}

void PDFS_Client::SendDelMsg()
{
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader->get_DelHeader().toHex()+"\n");
    server->SendMsg(tcpHeader->get_DelHeader());
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
    QByteArray serverReturn = server->GetServerMsg();
    ui->DebugInfo->append("[res]:" + serverReturn.toHex() +"\n");
    if(serverReturn.length()==21)
    {
        serverReturn.remove(0,1);
        qDebug("%lld",serverReturn.length());
        ui->DebugInfo->append("[res]:" + serverReturn.toHex() +"\n");
        Key=serverReturn;
        tcpHeader->set_Key(Key);
    }
}

void PDFS_Client::on_ServerConnect_clicked()
{
    ui->DebugInfo->append("Try to connect server");
    server->ConnectServer(ui->ServerHost->text(),ui->ServerPort->text().toUShort());
}

void PDFS_Client::on_Login_clicked()
{
    tcpHeader->set_op(opCode_Login);
    SendUserMsg();
}

void PDFS_Client::on_Register_clicked()
{
    tcpHeader->set_op(opCode_CreateUser);
    SendUserMsg();
}

void PDFS_Client::on_DeleteUser_clicked()
{
    tcpHeader->set_op(opCode_DeleteUser);
    SendDelMsg();
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
