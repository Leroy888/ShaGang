/********************************************************************************
** Form generated from reading UI file 'centerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTERWIDGET_H
#define UI_CENTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CenterWidget
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *CenterWidget)
    {
        if (CenterWidget->objectName().isEmpty())
            CenterWidget->setObjectName(QStringLiteral("CenterWidget"));
        CenterWidget->resize(400, 300);
        pushButton = new QPushButton(CenterWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 100, 75, 23));

        retranslateUi(CenterWidget);

        QMetaObject::connectSlotsByName(CenterWidget);
    } // setupUi

    void retranslateUi(QWidget *CenterWidget)
    {
        CenterWidget->setWindowTitle(QApplication::translate("CenterWidget", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CenterWidget", "one", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CenterWidget: public Ui_CenterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTERWIDGET_H
