/********************************************************************************
** Form generated from reading UI file 'SelectFromListDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTFROMLISTDIALOG_H
#define UI_SELECTFROMLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectFromListDialogClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *lineEdit;
    QListWidget *listWidget;

    void setupUi(QDialog *SelectFromListDialogClass)
    {
        if (SelectFromListDialogClass->objectName().isEmpty())
            SelectFromListDialogClass->setObjectName(QStringLiteral("SelectFromListDialogClass"));
        SelectFromListDialogClass->setWindowModality(Qt::ApplicationModal);
        SelectFromListDialogClass->resize(400, 300);
        SelectFromListDialogClass->setModal(true);
        layoutWidget = new QWidget(SelectFromListDialogClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 250, 361, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        lineEdit = new QLineEdit(SelectFromListDialogClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 10, 361, 20));
        listWidget = new QListWidget(SelectFromListDialogClass);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 30, 361, 221));

        retranslateUi(SelectFromListDialogClass);
        QObject::connect(okButton, SIGNAL(clicked()), SelectFromListDialogClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SelectFromListDialogClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectFromListDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SelectFromListDialogClass)
    {
        SelectFromListDialogClass->setWindowTitle(QApplication::translate("SelectFromListDialogClass", "Select From List", Q_NULLPTR));
        okButton->setText(QApplication::translate("SelectFromListDialogClass", "OK", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("SelectFromListDialogClass", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SelectFromListDialogClass: public Ui_SelectFromListDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTFROMLISTDIALOG_H
