/********************************************************************************
** Form generated from reading UI file 'procwatcher.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCWATCHER_H
#define UI_PROCWATCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcWatcher
{
public:
    QAction *actionProc_File_System;
    QAction *actionAbout;
    QAction *actionFind_Process_ID;
    QAction *actionStop;
    QAction *actionSet_Interval;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QTreeView *procTreeView;
    QPlainTextEdit *procText;
    QPlainTextEdit *fileInfoText;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuActions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProcWatcher)
    {
        if (ProcWatcher->objectName().isEmpty())
            ProcWatcher->setObjectName(QStringLiteral("ProcWatcher"));
        ProcWatcher->resize(905, 546);
        actionProc_File_System = new QAction(ProcWatcher);
        actionProc_File_System->setObjectName(QStringLiteral("actionProc_File_System"));
        actionAbout = new QAction(ProcWatcher);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionFind_Process_ID = new QAction(ProcWatcher);
        actionFind_Process_ID->setObjectName(QStringLiteral("actionFind_Process_ID"));
        actionStop = new QAction(ProcWatcher);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionStop->setEnabled(false);
        actionSet_Interval = new QAction(ProcWatcher);
        actionSet_Interval->setObjectName(QStringLiteral("actionSet_Interval"));
        centralWidget = new QWidget(ProcWatcher);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(4);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        procTreeView = new QTreeView(splitter);
        procTreeView->setObjectName(QStringLiteral("procTreeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(procTreeView->sizePolicy().hasHeightForWidth());
        procTreeView->setSizePolicy(sizePolicy1);
        splitter->addWidget(procTreeView);
        procText = new QPlainTextEdit(splitter);
        procText->setObjectName(QStringLiteral("procText"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(procText->sizePolicy().hasHeightForWidth());
        procText->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        procText->setFont(font);
        procText->setUndoRedoEnabled(false);
        procText->setLineWrapMode(QPlainTextEdit::NoWrap);
        procText->setReadOnly(true);
        splitter->addWidget(procText);
        splitter_2->addWidget(splitter);
        fileInfoText = new QPlainTextEdit(splitter_2);
        fileInfoText->setObjectName(QStringLiteral("fileInfoText"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(fileInfoText->sizePolicy().hasHeightForWidth());
        fileInfoText->setSizePolicy(sizePolicy3);
        fileInfoText->setFont(font);
        fileInfoText->setUndoRedoEnabled(false);
        fileInfoText->setReadOnly(true);
        splitter_2->addWidget(fileInfoText);

        verticalLayout->addWidget(splitter_2);

        ProcWatcher->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProcWatcher);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 905, 29));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QStringLiteral("menuActions"));
        ProcWatcher->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProcWatcher);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProcWatcher->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProcWatcher);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProcWatcher->setStatusBar(statusBar);

        menuBar->addAction(menuHelp->menuAction());
        menuBar->addAction(menuActions->menuAction());
        menuHelp->addAction(actionProc_File_System);
        menuHelp->addAction(actionAbout);
        menuActions->addAction(actionSet_Interval);
        menuActions->addAction(actionFind_Process_ID);
        menuActions->addAction(actionStop);

        retranslateUi(ProcWatcher);

        QMetaObject::connectSlotsByName(ProcWatcher);
    } // setupUi

    void retranslateUi(QMainWindow *ProcWatcher)
    {
        ProcWatcher->setWindowTitle(QApplication::translate("ProcWatcher", "ProcWatcher", 0));
        actionProc_File_System->setText(QApplication::translate("ProcWatcher", "Proc File System", 0));
        actionAbout->setText(QApplication::translate("ProcWatcher", "About", 0));
        actionFind_Process_ID->setText(QApplication::translate("ProcWatcher", "Find Process ID", 0));
        actionStop->setText(QApplication::translate("ProcWatcher", "Stop", 0));
        actionStop->setShortcut(QApplication::translate("ProcWatcher", "Ctrl+S", 0));
        actionSet_Interval->setText(QApplication::translate("ProcWatcher", "Set Interval", 0));
        menuHelp->setTitle(QApplication::translate("ProcWatcher", "Help", 0));
        menuActions->setTitle(QApplication::translate("ProcWatcher", "Actions", 0));
    } // retranslateUi

};

namespace Ui {
    class ProcWatcher: public Ui_ProcWatcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCWATCHER_H
