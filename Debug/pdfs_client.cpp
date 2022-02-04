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
    ui->ServerHost->setText("43.154.178.243");
    ui->ServerPort->setText("9999");
    ui->UserName->setText("YoitsuHolo");
    ui->Password->setText("YoitsuHolo");
    ui->FileTree->setColumnCount(3);
    ui->ULPath->setText("C:/Users/YoitsuHolo/Desktop/YoitsuHolo.txt");
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

//建立文件树
void PDFS_Client::BuildFileTree(QByteArray dirInfo)
{
    ui->DebugInfo->append(dirInfo.toHex());
    int num=dirInfo.front();
    int pos=1;
    QTextCodec *coding=QTextCodec::codecForName("UTF8");
    for(int i=1;i<=num;i++)
    {
        int FileType=dirInfo[pos++];
        int FileNameLen=dirInfo[pos++];
        QString FileName;
        FileName=coding->toUnicode(dirInfo.mid(pos,FileNameLen));
        pos+=FileNameLen;
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
    auto download=[=](QFile *file,QByteArray msg){new Download(file,msg);};//使用lambda表达式创建下载

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
        if(tempFile->exists())
            ui->DebugInfo->append("[文件存在]"+tempFile->fileName());
        else
        {
            ui->DebugInfo->append("[正在创建]"+tempFile->fileName());
            tempFile->open(QIODevice::ReadWrite);
        }
        tempFile->open(QIODevice::ReadWrite);
        download(tempFile,serverReturn);
        break;
    case stCode_FileUnexist:        //文件不存在
        break;
    case stCode_UploadSucceed:      //上传成功
        break;
    case stCode_DeleteFileSucceed:
        QMessageBox::warning(this,"Title",QString("删除文件成功"));
        break;
    case stCode_PathCreateSucceed:
        QMessageBox::warning(this,"Title",QString("创建文件夹成功"));
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
    QString fullPath=fileSystemModel->getPath();
    if(item->data(1,0).toString()!="<DIR>" && item->data(1,0).toString()!="<PRE>")
    {
        fullPath+="/";
        fullPath+=item->data(0,0).toString();
        fullPath+=".";
        fullPath+=item->data(1,0).toString();
    }
    ui->DLPath->setText(fullPath);
}

void PDFS_Client::on_FileTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->DebugInfo->append("user double clicked dir:    " + item->data(0,0).toString());
    if(item->data(1,0).toString()=="<DIR>")
        fileSystemModel->inPath(item->data(0,0).toString());
    else if(item->data(1,0).toString()=="<PRE>")
        fileSystemModel->outPath();

    ui->DLPath->setText(fileSystemModel->getPath());
    RefreshFileTree();
}

void PDFS_Client::on_UpLoad_clicked()
{
    QString path=ui->ULPath->text();
    QFile *uploadFile=new QFile(path);
    if(!uploadFile->exists())
    {
        QMessageBox::warning(this,"文件不存在",QString("文件不存在"));
        return;
    }
    if(!uploadFile->open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"文件不可读",QString("文件不可读"));
        return;
    }
    Upload* up=new Upload(ui->ServerHost->text(),ui->ServerPort->text().toUShort(),uploadFile,"/",tcpHeader);
    ui->UploadProgress->setRange(0,100);
    ui->UploadProgress->setValue(0);
    connect(up,&Upload::proccess,ui->UploadProgress,&QProgressBar::setValue);
}

void PDFS_Client::on_Download_clicked()
{
    //header.clear();
    QString serverPath=ui->DLPath->text();
    //ui->DLPath->setEnabled(false);
    serverPath.remove(0,1);
    QString localPath="D:/code/git/PDFS-Test/"+serverPath.split("/").back();

    ui->DebugInfo->append("Download File:"+serverPath);
    //ui->DebugInfo->append("File:"+FileName);
    tempFile = new QFile(localPath);
    ui->DebugInfo->append("正在获取服务器数据");
    QByteArray header;
    tcpHeader->set_op(opCode_DownloadFile);
    std::stringstream ss;

    header.append(tcpHeader->get_KeyHeader());

    header.append(serverPath.toUtf8());
    ui->DebugInfo->append(serverPath);


    server->SendMsg(header);
}

void PDFS_Client::on_DebugSend_clicked()
{
    QString serverPath=ui->DLPath->text();
    serverPath.remove(0,1);
    ui->DebugInfo->append("delete: "+serverPath);
    QString content=ui->DebugCommand->text();
    QByteArray header;
    if(content == "deletefile")
    {

        tcpHeader->set_op(opCode_DeleteFile);
        header.append(tcpHeader->get_KeyHeader()).append(serverPath.toLatin1());
        server->SendMsg(header);
    }
    if(content == "createpath")
    {
        tcpHeader->set_op(opCode_CreatePath);
        header.append(tcpHeader->get_KeyHeader()).append(serverPath.toLatin1());
        server->SendMsg(header);
    }
    ui->DebugInfo->append(header.toHex());
}

