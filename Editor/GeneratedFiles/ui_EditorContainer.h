/********************************************************************************
** Form generated from reading UI file 'EditorContainer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORCONTAINER_H
#define UI_EDITORCONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorContainerClass
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Quit;
    QAction *action_Sprite;
    QAction *action_Undo;
    QAction *action_Redo;
    QAction *action_StartServer;
    QAction *action_LaunchClients;
    QAction *action_TestBuild;
    QAction *action_TestBuildWithoutOneClient;
    QAction *action_TestBuildWithBots;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu_New;
    QMenu *menuEdit;
    QMenu *menuRun;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditorContainerClass)
    {
        if (EditorContainerClass->objectName().isEmpty())
            EditorContainerClass->setObjectName(QStringLiteral("EditorContainerClass"));
        EditorContainerClass->resize(475, 352);
        action_Open = new QAction(EditorContainerClass);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Save = new QAction(EditorContainerClass);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        action_Quit = new QAction(EditorContainerClass);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Sprite = new QAction(EditorContainerClass);
        action_Sprite->setObjectName(QStringLiteral("action_Sprite"));
        action_Undo = new QAction(EditorContainerClass);
        action_Undo->setObjectName(QStringLiteral("action_Undo"));
        action_Redo = new QAction(EditorContainerClass);
        action_Redo->setObjectName(QStringLiteral("action_Redo"));
        action_StartServer = new QAction(EditorContainerClass);
        action_StartServer->setObjectName(QStringLiteral("action_StartServer"));
        action_LaunchClients = new QAction(EditorContainerClass);
        action_LaunchClients->setObjectName(QStringLiteral("action_LaunchClients"));
        action_TestBuild = new QAction(EditorContainerClass);
        action_TestBuild->setObjectName(QStringLiteral("action_TestBuild"));
        action_TestBuildWithoutOneClient = new QAction(EditorContainerClass);
        action_TestBuildWithoutOneClient->setObjectName(QStringLiteral("action_TestBuildWithoutOneClient"));
        action_TestBuildWithBots = new QAction(EditorContainerClass);
        action_TestBuildWithBots->setObjectName(QStringLiteral("action_TestBuildWithBots"));
        centralWidget = new QWidget(EditorContainerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        EditorContainerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorContainerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 475, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menu_New = new QMenu(menuFile);
        menu_New->setObjectName(QStringLiteral("menu_New"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuRun = new QMenu(menuBar);
        menuRun->setObjectName(QStringLiteral("menuRun"));
        EditorContainerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(EditorContainerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EditorContainerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuRun->menuAction());
        menuFile->addAction(menu_New->menuAction());
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Save);
        menuFile->addSeparator();
        menuFile->addAction(action_Quit);
        menuEdit->addAction(action_Undo);
        menuEdit->addAction(action_Redo);
        menuRun->addAction(action_TestBuild);
        menuRun->addAction(action_TestBuildWithoutOneClient);
        menuRun->addAction(action_TestBuildWithBots);

        retranslateUi(EditorContainerClass);

        QMetaObject::connectSlotsByName(EditorContainerClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorContainerClass)
    {
        EditorContainerClass->setWindowTitle(QApplication::translate("EditorContainerClass", "StormBrewer Engine", Q_NULLPTR));
        action_Open->setText(QApplication::translate("EditorContainerClass", "&Open", Q_NULLPTR));
        action_Save->setText(QApplication::translate("EditorContainerClass", "Save", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("EditorContainerClass", "&Quit", Q_NULLPTR));
        action_Sprite->setText(QApplication::translate("EditorContainerClass", "Sprite", Q_NULLPTR));
        action_Undo->setText(QApplication::translate("EditorContainerClass", "Undo", Q_NULLPTR));
        action_Redo->setText(QApplication::translate("EditorContainerClass", "Redo", Q_NULLPTR));
        action_StartServer->setText(QApplication::translate("EditorContainerClass", "Start Server", Q_NULLPTR));
        action_LaunchClients->setText(QApplication::translate("EditorContainerClass", "Launch Clients", Q_NULLPTR));
        action_TestBuild->setText(QApplication::translate("EditorContainerClass", "Test Build", Q_NULLPTR));
        action_TestBuildWithoutOneClient->setText(QApplication::translate("EditorContainerClass", "Test Build Without One Client", Q_NULLPTR));
        action_TestBuildWithBots->setText(QApplication::translate("EditorContainerClass", "Test Build With Bots", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("EditorContainerClass", "&File", Q_NULLPTR));
        menu_New->setTitle(QApplication::translate("EditorContainerClass", "&New", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("EditorContainerClass", "Edit", Q_NULLPTR));
        menuRun->setTitle(QApplication::translate("EditorContainerClass", "Run", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditorContainerClass: public Ui_EditorContainerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORCONTAINER_H
