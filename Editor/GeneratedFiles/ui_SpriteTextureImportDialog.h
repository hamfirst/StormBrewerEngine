/********************************************************************************
** Form generated from reading UI file 'SpriteTextureImportDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITETEXTUREIMPORTDIALOG_H
#define UI_SPRITETEXTUREIMPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpriteTextureImport
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *frameWidth;
    QLineEdit *frameHeight;

    void setupUi(QDialog *SpriteTextureImport)
    {
        if (SpriteTextureImport->objectName().isEmpty())
            SpriteTextureImport->setObjectName(QStringLiteral("SpriteTextureImport"));
        SpriteTextureImport->resize(767, 421);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SpriteTextureImport->sizePolicy().hasHeightForWidth());
        SpriteTextureImport->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(SpriteTextureImport);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(560, 370, 181, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        label = new QLabel(SpriteTextureImport);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(26, 350, 81, 21));
        label_2 = new QLabel(SpriteTextureImport);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(26, 380, 81, 21));
        frameWidth = new QLineEdit(SpriteTextureImport);
        frameWidth->setObjectName(QStringLiteral("frameWidth"));
        frameWidth->setGeometry(QRect(120, 350, 113, 20));
        frameHeight = new QLineEdit(SpriteTextureImport);
        frameHeight->setObjectName(QStringLiteral("frameHeight"));
        frameHeight->setGeometry(QRect(120, 380, 113, 20));

        retranslateUi(SpriteTextureImport);
        QObject::connect(okButton, SIGNAL(clicked()), SpriteTextureImport, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SpriteTextureImport, SLOT(reject()));

        QMetaObject::connectSlotsByName(SpriteTextureImport);
    } // setupUi

    void retranslateUi(QDialog *SpriteTextureImport)
    {
        SpriteTextureImport->setWindowTitle(QApplication::translate("SpriteTextureImport", "Texture Import", nullptr));
        okButton->setText(QApplication::translate("SpriteTextureImport", "OK", nullptr));
        cancelButton->setText(QApplication::translate("SpriteTextureImport", "Cancel", nullptr));
        label->setText(QApplication::translate("SpriteTextureImport", "Frame Width", nullptr));
        label_2->setText(QApplication::translate("SpriteTextureImport", "Frame Height", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpriteTextureImport: public Ui_SpriteTextureImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITETEXTUREIMPORTDIALOG_H
