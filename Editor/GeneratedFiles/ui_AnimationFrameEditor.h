/********************************************************************************
** Form generated from reading UI file 'AnimationFrameEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONFRAMEEDITOR_H
#define UI_ANIMATIONFRAMEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnimationFrameEditor
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AnimationFrameEditor)
    {
        if (AnimationFrameEditor->objectName().isEmpty())
            AnimationFrameEditor->setObjectName(QStringLiteral("AnimationFrameEditor"));
        AnimationFrameEditor->resize(971, 693);
        layoutWidget = new QWidget(AnimationFrameEditor);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(610, 650, 351, 33));
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


        retranslateUi(AnimationFrameEditor);
        QObject::connect(okButton, SIGNAL(clicked()), AnimationFrameEditor, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), AnimationFrameEditor, SLOT(reject()));

        QMetaObject::connectSlotsByName(AnimationFrameEditor);
    } // setupUi

    void retranslateUi(QDialog *AnimationFrameEditor)
    {
        AnimationFrameEditor->setWindowTitle(QApplication::translate("AnimationFrameEditor", "Animation Frame Editor", nullptr));
        okButton->setText(QApplication::translate("AnimationFrameEditor", "OK", nullptr));
        cancelButton->setText(QApplication::translate("AnimationFrameEditor", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnimationFrameEditor: public Ui_AnimationFrameEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONFRAMEEDITOR_H
