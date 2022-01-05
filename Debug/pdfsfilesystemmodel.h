#ifndef PDFSFILESYSTEMMODEL_H
#define PDFSFILESYSTEMMODEL_H

#include <QList>
#include <QString>

#include "pdfsdirmodel.h"

class PDFSFileSystemModel
{
private:
    PDFSDirModel *root;
    PDFSDirModel *now;
    QList<QString> path;
    QString fullPath;

public:
    PDFSFileSystemModel();

public:
    void TEST();
    void StepInDir(QString DirName);
    QList<QStringList> GetFileSystemStruct();
};

#endif // PDFSFILESYSTEMMODEL_H
