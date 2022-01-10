/********************************************************************************
** Form generated from reading UI file 'pdfs_client.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFS_CLIENT_H
#define UI_PDFS_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PDFS_Client
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *SHost;
    QLineEdit *ServerHost;
    QLabel *SState;
    QLineEdit *ServerState;
    QPushButton *ServerConnect;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *UserArea;
    QHBoxLayout *UserNameLayout;
    QLabel *UserNameLabel;
    QLineEdit *UserName;
    QHBoxLayout *PasswordLayout;
    QLabel *PasswordLabel;
    QLineEdit *Password;
    QPushButton *Login;
    QTreeWidget *FileTree;
    QHBoxLayout *DLPathLayout;
    QLabel *DLPathLabel;
    QLineEdit *DLPath;
    QPushButton *Download;
    QHBoxLayout *ULPathLayout;
    QLabel *ULPathLabel;
    QLineEdit *ULPath;
    QPushButton *UpLoad;
    QVBoxLayout *DebugArea;
    QHBoxLayout *DebugLayout;
    QLabel *DebugLabel;
    QLineEdit *DebugCommand;
    QPushButton *DebugSend;
    QTextEdit *DebugInfo;
    QHBoxLayout *DownLoadLayout;
    QLabel *DownloadLabel;
    QProgressBar *DownloadProgress;
    QHBoxLayout *UploadLayout;
    QLabel *UploadLabel;
    QProgressBar *UploadProgress;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PDFS_Client)
    {
        if (PDFS_Client->objectName().isEmpty())
            PDFS_Client->setObjectName(QString::fromUtf8("PDFS_Client"));
        PDFS_Client->resize(700, 500);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PDFS_Client->sizePolicy().hasHeightForWidth());
        PDFS_Client->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(PDFS_Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(700, 450));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        SHost = new QLabel(centralwidget);
        SHost->setObjectName(QString::fromUtf8("SHost"));

        horizontalLayout_8->addWidget(SHost);

        ServerHost = new QLineEdit(centralwidget);
        ServerHost->setObjectName(QString::fromUtf8("ServerHost"));

        horizontalLayout_8->addWidget(ServerHost);

        SState = new QLabel(centralwidget);
        SState->setObjectName(QString::fromUtf8("SState"));

        horizontalLayout_8->addWidget(SState);

        ServerState = new QLineEdit(centralwidget);
        ServerState->setObjectName(QString::fromUtf8("ServerState"));
        ServerState->setMaximumSize(QSize(80, 16777215));
        ServerState->setReadOnly(false);

        horizontalLayout_8->addWidget(ServerState);

        ServerConnect = new QPushButton(centralwidget);
        ServerConnect->setObjectName(QString::fromUtf8("ServerConnect"));

        horizontalLayout_8->addWidget(ServerConnect);


        gridLayout->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        UserArea = new QVBoxLayout();
        UserArea->setObjectName(QString::fromUtf8("UserArea"));
        UserArea->setSizeConstraint(QLayout::SetMinAndMaxSize);
        UserArea->setContentsMargins(-1, -1, 0, 0);
        UserNameLayout = new QHBoxLayout();
        UserNameLayout->setObjectName(QString::fromUtf8("UserNameLayout"));
        UserNameLabel = new QLabel(centralwidget);
        UserNameLabel->setObjectName(QString::fromUtf8("UserNameLabel"));
        UserNameLabel->setMinimumSize(QSize(100, 0));
        UserNameLabel->setMaximumSize(QSize(100, 16777215));

        UserNameLayout->addWidget(UserNameLabel);

        UserName = new QLineEdit(centralwidget);
        UserName->setObjectName(QString::fromUtf8("UserName"));

        UserNameLayout->addWidget(UserName);


        UserArea->addLayout(UserNameLayout);

        PasswordLayout = new QHBoxLayout();
        PasswordLayout->setObjectName(QString::fromUtf8("PasswordLayout"));
        PasswordLabel = new QLabel(centralwidget);
        PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));
        PasswordLabel->setMinimumSize(QSize(100, 0));
        PasswordLabel->setMaximumSize(QSize(100, 16777215));

        PasswordLayout->addWidget(PasswordLabel);

        Password = new QLineEdit(centralwidget);
        Password->setObjectName(QString::fromUtf8("Password"));

        PasswordLayout->addWidget(Password);


        UserArea->addLayout(PasswordLayout);

        Login = new QPushButton(centralwidget);
        Login->setObjectName(QString::fromUtf8("Login"));

        UserArea->addWidget(Login);

        FileTree = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        FileTree->setHeaderItem(__qtreewidgetitem);
        FileTree->setObjectName(QString::fromUtf8("FileTree"));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        FileTree->setFont(font);

        UserArea->addWidget(FileTree);

        DLPathLayout = new QHBoxLayout();
        DLPathLayout->setObjectName(QString::fromUtf8("DLPathLayout"));
        DLPathLabel = new QLabel(centralwidget);
        DLPathLabel->setObjectName(QString::fromUtf8("DLPathLabel"));
        DLPathLabel->setMinimumSize(QSize(60, 0));
        DLPathLabel->setMaximumSize(QSize(60, 16777215));

        DLPathLayout->addWidget(DLPathLabel);

        DLPath = new QLineEdit(centralwidget);
        DLPath->setObjectName(QString::fromUtf8("DLPath"));

        DLPathLayout->addWidget(DLPath);

        Download = new QPushButton(centralwidget);
        Download->setObjectName(QString::fromUtf8("Download"));

        DLPathLayout->addWidget(Download);


        UserArea->addLayout(DLPathLayout);

        ULPathLayout = new QHBoxLayout();
        ULPathLayout->setObjectName(QString::fromUtf8("ULPathLayout"));
        ULPathLabel = new QLabel(centralwidget);
        ULPathLabel->setObjectName(QString::fromUtf8("ULPathLabel"));
        ULPathLabel->setMinimumSize(QSize(60, 0));
        ULPathLabel->setMaximumSize(QSize(60, 16777215));

        ULPathLayout->addWidget(ULPathLabel);

        ULPath = new QLineEdit(centralwidget);
        ULPath->setObjectName(QString::fromUtf8("ULPath"));

        ULPathLayout->addWidget(ULPath);

        UpLoad = new QPushButton(centralwidget);
        UpLoad->setObjectName(QString::fromUtf8("UpLoad"));

        ULPathLayout->addWidget(UpLoad);


        UserArea->addLayout(ULPathLayout);


        horizontalLayout_7->addLayout(UserArea);

        DebugArea = new QVBoxLayout();
        DebugArea->setObjectName(QString::fromUtf8("DebugArea"));
        DebugLayout = new QHBoxLayout();
        DebugLayout->setObjectName(QString::fromUtf8("DebugLayout"));
        DebugLabel = new QLabel(centralwidget);
        DebugLabel->setObjectName(QString::fromUtf8("DebugLabel"));

        DebugLayout->addWidget(DebugLabel);

        DebugCommand = new QLineEdit(centralwidget);
        DebugCommand->setObjectName(QString::fromUtf8("DebugCommand"));

        DebugLayout->addWidget(DebugCommand);

        DebugSend = new QPushButton(centralwidget);
        DebugSend->setObjectName(QString::fromUtf8("DebugSend"));

        DebugLayout->addWidget(DebugSend);


        DebugArea->addLayout(DebugLayout);

        DebugInfo = new QTextEdit(centralwidget);
        DebugInfo->setObjectName(QString::fromUtf8("DebugInfo"));

        DebugArea->addWidget(DebugInfo);

        DownLoadLayout = new QHBoxLayout();
        DownLoadLayout->setObjectName(QString::fromUtf8("DownLoadLayout"));
        DownloadLabel = new QLabel(centralwidget);
        DownloadLabel->setObjectName(QString::fromUtf8("DownloadLabel"));
        DownloadLabel->setMinimumSize(QSize(100, 0));

        DownLoadLayout->addWidget(DownloadLabel);

        DownloadProgress = new QProgressBar(centralwidget);
        DownloadProgress->setObjectName(QString::fromUtf8("DownloadProgress"));
        DownloadProgress->setValue(24);

        DownLoadLayout->addWidget(DownloadProgress);


        DebugArea->addLayout(DownLoadLayout);

        UploadLayout = new QHBoxLayout();
        UploadLayout->setObjectName(QString::fromUtf8("UploadLayout"));
        UploadLabel = new QLabel(centralwidget);
        UploadLabel->setObjectName(QString::fromUtf8("UploadLabel"));
        UploadLabel->setMinimumSize(QSize(100, 0));

        UploadLayout->addWidget(UploadLabel);

        UploadProgress = new QProgressBar(centralwidget);
        UploadProgress->setObjectName(QString::fromUtf8("UploadProgress"));
        UploadProgress->setValue(24);

        UploadLayout->addWidget(UploadProgress);


        DebugArea->addLayout(UploadLayout);


        horizontalLayout_7->addLayout(DebugArea);


        gridLayout->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        PDFS_Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PDFS_Client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 26));
        PDFS_Client->setMenuBar(menubar);
        statusbar = new QStatusBar(PDFS_Client);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PDFS_Client->setStatusBar(statusbar);
        QWidget::setTabOrder(Login, FileTree);
        QWidget::setTabOrder(FileTree, DebugCommand);
        QWidget::setTabOrder(DebugCommand, DebugSend);
        QWidget::setTabOrder(DebugSend, DebugInfo);

        retranslateUi(PDFS_Client);

        QMetaObject::connectSlotsByName(PDFS_Client);
    } // setupUi

    void retranslateUi(QMainWindow *PDFS_Client)
    {
        PDFS_Client->setWindowTitle(QCoreApplication::translate("PDFS_Client", "PDFS_Client", nullptr));
        SHost->setText(QCoreApplication::translate("PDFS_Client", "Host:", nullptr));
        SState->setText(QCoreApplication::translate("PDFS_Client", "State:", nullptr));
        ServerConnect->setText(QCoreApplication::translate("PDFS_Client", "connect", nullptr));
        UserNameLabel->setText(QCoreApplication::translate("PDFS_Client", "UserName:", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("PDFS_Client", "Password:", nullptr));
        Login->setText(QCoreApplication::translate("PDFS_Client", "Login", nullptr));
        DLPathLabel->setText(QCoreApplication::translate("PDFS_Client", "DLPath:", nullptr));
        Download->setText(QCoreApplication::translate("PDFS_Client", "Download", nullptr));
        ULPathLabel->setText(QCoreApplication::translate("PDFS_Client", "ULPath:", nullptr));
        UpLoad->setText(QCoreApplication::translate("PDFS_Client", "Upload", nullptr));
        DebugLabel->setText(QCoreApplication::translate("PDFS_Client", "Debug:", nullptr));
        DebugSend->setText(QCoreApplication::translate("PDFS_Client", "Send", nullptr));
        DownloadLabel->setText(QCoreApplication::translate("PDFS_Client", "DownLoad:", nullptr));
        UploadLabel->setText(QCoreApplication::translate("PDFS_Client", "UpLoad:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PDFS_Client: public Ui_PDFS_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFS_CLIENT_H
