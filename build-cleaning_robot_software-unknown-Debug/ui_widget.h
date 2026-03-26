/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 60, 191, 71));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(330, 250, 171, 41));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 150, 191, 71));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 240, 191, 71));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(40, 320, 191, 81));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(40, 420, 191, 81));
        pushButton_6 = new QPushButton(Widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(500, 50, 171, 91));
        pushButton_7 = new QPushButton(Widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(500, 160, 171, 81));
        pushButton_8 = new QPushButton(Widget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(500, 270, 171, 81));
        pushButton_9 = new QPushButton(Widget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(500, 370, 171, 81));
        pushButton_10 = new QPushButton(Widget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(500, 470, 171, 91));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\345\220\257\345\212\250\346\234\272\345\231\250\344\272\272\345\272\225\345\261\202", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\212\266\346\200\201\357\274\232\346\234\252\345\220\257\345\212\250", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\346\234\272\345\231\250\344\272\272", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\345\220\257\345\212\250\345\273\272\345\233\276", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\345\220\257\345\212\250\351\224\256\347\233\230\346\216\247\345\210\266", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\345\234\260\345\233\276", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Widget", "\345\220\257\345\212\250\345\257\274\350\210\252", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\346\211\253\345\234\260", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\346\211\253\345\234\260", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\350\246\206\347\233\226\346\270\205\346\211\253", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200Riz2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
