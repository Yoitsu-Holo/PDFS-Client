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
    ui->ULPath->setText("C:/Users/YoitsuHolo/Desktop/账号密码.txt");
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

void PDFS_Client::RefreshFileTree()
{
    QList<QTreeWidgetItem *> items;
    QList<QStringList> fileStruct = fileSystemModel->CtoQ_FileTree(fileSystemModel->getFileTree());
    for (auto && fileEle:fileStruct)
        items.append(new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), fileEle));
    ui->FileTree->clear();
    ui->FileTree->insertTopLevelItems(0,items);
}

void PDFS_Client::RequestFileTree(QString Path)
{
    tcpHeader->set_op(opCode_RequestDir);
    QByteArray temp=tcpHeader->get_KeyHeader();
    temp.append(Path.toLatin1());
    ui->DebugInfo->append("out:"+temp.toHex());
    server->SendMsg(temp);
}

void PDFS_Client::BuildFileTree(QByteArray dirInfo)
{
    ui->DebugInfo->append(dirInfo.toHex());
    int num=dirInfo.front();
    int pos=1;
    for(int i=1;i<=num;i++)
    {
        int FileType=dirInfo[pos++];
        int FileNameLen=dirInfo[pos++];
        QString FileName;
        for(int j=1;j<=FileNameLen;j++)
            FileName.append(dirInfo[pos++]);
        switch(FileType)
        {
        case 1:
            fileSystemModel->addFile(FileName,0);
            break;
        case 2:
            fileSystemModel->addDir(FileName);
            break;
        }
    }
}

//服务器相应
void PDFS_Client::onServerReturned()
{
    QByteArray serverReturn = server->GetServerMsg();
    ui->DebugInfo->append("[res]:" + serverReturn.toHex() +"\n");
    int serverCode=(unsigned int) serverReturn.front();
    serverReturn.remove(0,1);
    switch(serverCode)
    {
    case stCode_Undefined:          //未定义操作
        QMessageBox::information(this,"Title",QString("未知错误"));
        break;
    case stCode_LoginSucceed:       //登录成功
        QMessageBox::information(this,"Title",QString("登录成功"));
        Key=serverReturn;
        ui->DebugInfo->append("KEY:"+Key.toHex()+"\n");
        tcpHeader->set_Key(Key);
        //RequestFileTree("/");
        break;
    case stCode_LoginPWDError:      //登录密码错误
        QMessageBox::warning(this,"Title",QString("密码错误"));
        break;
    case stCode_CreateUserSucceed:  //创建用户成功
        break;
    case stCode_UserExist:          //用户已存在
        QMessageBox::warning(this,"Title",QString("用户已存在"));
        break;
    case stCode_DeleteUserSucceed:  //删除用户成功
        break;
    case stCode_DeleteUserPWDFail:  //删除用户时验证密码失败
        QMessageBox::warning(this,"Title",QString("密码错误"));
        break;
    case stCode_GetFileTreeSucceed: //获取文件树成功
        BuildFileTree(serverReturn);
        RefreshFileTree();
        break;
    case stCode_DownloadReturn:     //下载请求返回成功
        break;
    case stCode_FileUnexist:        //文件不存在
        break;
    case stCode_UploadSucceed:      //上传成功
        break;
    default:
        QMessageBox::information(this,"Title",QString("未定义操作：")+QString::number(serverCode));
        break;
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
    tcpHeader->set_UserName(ui->UserName->text());
    tcpHeader->set_Password(ui->Password->text());
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader->get_UserHeader().toHex()+"\n");
    server->SendMsg(tcpHeader->get_UserHeader());
}

void PDFS_Client::on_Register_clicked()
{
    tcpHeader->set_op(opCode_CreateUser);
    tcpHeader->set_UserName(ui->UserName->text());
    tcpHeader->set_Password(ui->Password->text());
    ui->DebugInfo->append("Hex Header:\n" + tcpHeader->get_UserHeader().toHex()+"\n");
    server->SendMsg(tcpHeader->get_UserHeader());
}

void PDFS_Client::on_DeleteUser_clicked()   //临时测试
{
    RequestFileTree("/");
//    tcpHeader->set_op(opCode_DeleteUser);
//    ui->DebugInfo->append("Hex Header:\n" + tcpHeader->get_DelHeader().toHex()+"\n");
//    server->SendMsg(tcpHeader->get_DelHeader());
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

void PDFS_Client::on_UpLoad_clicked()
{
    QString path=ui->ULPath->text();
    QFile uploadFile(path);
    if(!uploadFile.exists())
        QMessageBox::warning(this,"文件不存在",QString("文件不存在"));
    if(!uploadFile.open(QIODevice::ReadOnly))
        QMessageBox::warning(this,"不可读",QString("不可读"));
    ui->DebugInfo->append(uploadFile.readAll().toHex());
}

