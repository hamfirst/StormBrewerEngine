/********************************************************************************
** Form generated from reading UI file 'ConnectingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTINGDIALOG_H
#define UI_CONNECTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectingDialogClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *cancelButton;
    QLabel *label;

    void setupUi(QDialog *ConnectingDialogClass)
    {
        if (ConnectingDialogClass->objectName().isEmpty())
            ConnectingDialogClass->setObjectName(QStringLiteral("ConnectingDialogClass"));
        ConnectingDialogClass->resize(412, 127);
        layoutWidget = new QWidget(ConnectingDialogClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 70, 151, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        label = new QLabel(ConnectingDialogClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 30, 181, 20));

        retranslateUi(ConnectingDialogClass);
        QObject::connect(cancelButton, SIGNAL(clicked()), ConnectingDialogClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConnectingDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ConnectingDialogClass)
    {
        ConnectingDialogClass->setWindowTitle(QApplication::translate("ConnectingDialogClass", "Connection...", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("ConnectingDialogClass", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("ConnectingDialogClass", "Connecting To Document Server...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectingDialogClass: public Ui_ConnectingDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTINGDIALOG_H
