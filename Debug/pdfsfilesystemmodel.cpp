#include "pdfsfilesystemmodel.h"

PDFSFileSystemModel::PDFSFileSystemModel()
{
    root = new PDFSDirModel;
    now = root;
}

void PDFSFileSystemModel::TEST()
{
    PDFSDirModel* newDir;
    PDFSFileModel* newFile;
    char shacode[]="bb29df19e87cc33c03888d097dcb81cc24702d68c5d065543fc9d9d09f86cd72";
    now=root;
    for(int i=0;i<5;i++)
    {
        newDir = new PDFSDirModel;
        newFile = new PDFSFileModel;
        newDir->SetDirInfo(QChar(i+'a'),2022,1,5,shacode);
        newFile->SetFileInfo("File"+QString(QChar(i+'0')) ,2022,1,5,shacode,i);
        now->AddDir(*newDir);
        qDebug("next");
        now->AddFile(*newFile);
    }
    now=now->Dir(QString("a"));
    for(int i=0;i<5;i++)
    {
        newDir = new PDFSDirModel;
        newFile = new PDFSFileModel;
        newDir->SetDirInfo(QChar(i+'a'),2022,1,5,shacode);
        newFile->SetFileInfo("File"+QString(QChar(i+'0')) ,2022,1,5,shacode,i);
        now->AddDir(*newDir);
        now->AddFile(*newFile);
    }
    now=root;
}

void PDFSFileSystemModel::StepInDir(QString DirName)
{
    now=now->Dir(DirName);
    return ;
}

QList<QStringList> PDFSFileSystemModel::GetFileSystemStruct()
{
    QList<QStringList> FileStruct;
    FileStruct.append(now->AllDir());
    FileStruct.append(now->AllFile());
    return FileStruct;
}
