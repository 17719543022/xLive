/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "extendqlabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widgetAll;
    QLabel *labelIdImage;
    QLabel *labelMeitou;
    QLabel *labelMeitouText;
    QLabel *labelRightMeitou;
    QLabel *labelRightMeitouText_1;
    QLabel *labelRightMeitouText_2;
    extendQLabel *labelXImage;
    QPushButton *pushButtonNImage;
    QPushButton *pushButtonUpLoad;
    QTableWidget *tableWidgetBottom;
    QTableWidget *tableWidgetRight;
    QWidget *widgetDlg;
    QWidget *widgetBox;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonConfirm;
    QPushButton *pushButtonAccept;
    QPushButton *pushButtonReject;
    QLabel *labelText;
    QPushButton *pushButtonAccept_2;
    QPushButton *pushButtonReject_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        widgetAll = new QWidget(centralwidget);
        widgetAll->setObjectName(QString::fromUtf8("widgetAll"));
        widgetAll->setGeometry(QRect(0, 0, 1920, 1080));
        widgetAll->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 65, 109);"));
        labelIdImage = new QLabel(widgetAll);
        labelIdImage->setObjectName(QString::fromUtf8("labelIdImage"));
        labelIdImage->setGeometry(QRect(748, 651, 252, 194));
        labelIdImage->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 102, 105);\n"
"border: 0;\n"
"image: 0;"));
        labelMeitou = new QLabel(widgetAll);
        labelMeitou->setObjectName(QString::fromUtf8("labelMeitou"));
        labelMeitou->setGeometry(QRect(0, 0, 1920, 65));
        QFont font;
        font.setPointSize(30);
        labelMeitou->setFont(font);
        labelMeitou->setStyleSheet(QString::fromUtf8("background-color: rgb(31, 46, 73);"));
        labelMeitouText = new QLabel(widgetAll);
        labelMeitouText->setObjectName(QString::fromUtf8("labelMeitouText"));
        labelMeitouText->setGeometry(QRect(10, 0, 400, 65));
        labelMeitouText->setFont(font);
        labelMeitouText->setStyleSheet(QString::fromUtf8("background: 0;\n"
"color: rgb(255, 255, 255);"));
        labelRightMeitou = new QLabel(widgetAll);
        labelRightMeitou->setObjectName(QString::fromUtf8("labelRightMeitou"));
        labelRightMeitou->setGeometry(QRect(1282, 75, 628, 65));
        QFont font1;
        font1.setPointSize(25);
        labelRightMeitou->setFont(font1);
        labelRightMeitou->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 25, 42);"));
        labelRightMeitouText_1 = new QLabel(widgetAll);
        labelRightMeitouText_1->setObjectName(QString::fromUtf8("labelRightMeitouText_1"));
        labelRightMeitouText_1->setGeometry(QRect(1292, 75, 351, 65));
        labelRightMeitouText_1->setFont(font1);
        labelRightMeitouText_1->setStyleSheet(QString::fromUtf8("background: 0;\n"
"color: rgb(0, 252, 255);"));
        labelRightMeitouText_2 = new QLabel(widgetAll);
        labelRightMeitouText_2->setObjectName(QString::fromUtf8("labelRightMeitouText_2"));
        labelRightMeitouText_2->setGeometry(QRect(1660, 75, 250, 65));
        labelRightMeitouText_2->setFont(font1);
        labelRightMeitouText_2->setStyleSheet(QString::fromUtf8("background: 0;\n"
"color: rgb(0, 252, 255);"));
        labelXImage = new extendQLabel(widgetAll);
        labelXImage->setObjectName(QString::fromUtf8("labelXImage"));
        labelXImage->setGeometry(QRect(10, 75, 1262, 780));
        labelXImage->setContextMenuPolicy(Qt::DefaultContextMenu);
        labelXImage->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 224, 229);"));
        pushButtonNImage = new QPushButton(widgetAll);
        pushButtonNImage->setObjectName(QString::fromUtf8("pushButtonNImage"));
        pushButtonNImage->setGeometry(QRect(1010, 651, 252, 194));
        pushButtonNImage->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 102, 105);\n"
"border: 0;\n"
"image: 0;"));
        pushButtonUpLoad = new QPushButton(widgetAll);
        pushButtonUpLoad->setObjectName(QString::fromUtf8("pushButtonUpLoad"));
        pushButtonUpLoad->setGeometry(QRect(1282, 790, 628, 65));
        QFont font2;
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        pushButtonUpLoad->setFont(font2);
        pushButtonUpLoad->setStyleSheet(QString::fromUtf8("border: 0;\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(4, 185, 118);\n"
"border-radius:8px;"));
        tableWidgetBottom = new QTableWidget(widgetAll);
        tableWidgetBottom->setObjectName(QString::fromUtf8("tableWidgetBottom"));
        tableWidgetBottom->setGeometry(QRect(5, 865, 1905, 205));
        tableWidgetBottom->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background-color: rgb(1, 65, 109);"));
        tableWidgetRight = new QTableWidget(widgetAll);
        tableWidgetRight->setObjectName(QString::fromUtf8("tableWidgetRight"));
        tableWidgetRight->setGeometry(QRect(1282, 145, 628, 635));
        tableWidgetRight->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background-color: rgb(1, 65, 109);"));
        tableWidgetRight->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        labelMeitou->raise();
        labelMeitouText->raise();
        labelRightMeitou->raise();
        labelRightMeitouText_1->raise();
        labelRightMeitouText_2->raise();
        labelXImage->raise();
        labelIdImage->raise();
        pushButtonNImage->raise();
        pushButtonUpLoad->raise();
        tableWidgetBottom->raise();
        tableWidgetRight->raise();
        widgetDlg = new QWidget(centralwidget);
        widgetDlg->setObjectName(QString::fromUtf8("widgetDlg"));
        widgetDlg->setGeometry(QRect(0, 0, 1920, 1080));
        widgetDlg->setStyleSheet(QString::fromUtf8("border: 0;\n"
"background-color: rgba(0, 0, 0, 0.5);"));
        widgetBox = new QWidget(widgetDlg);
        widgetBox->setObjectName(QString::fromUtf8("widgetBox"));
        widgetBox->setGeometry(QRect(596, 310, 728, 426));
        widgetBox->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 43, 68);"));
        pushButtonClose = new QPushButton(widgetBox);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(665, 15, 47, 45));
        pushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton{image: 0; background: 0; border-image: url(:/new/prefix1/Images/\345\205\263--\351\227\255-\346\213\267\350\264\235.png);}\n"
"QPushButton:pressed{image: 0; background: 0; border-image: url(:/new/prefix1/Images/\345\205\263--\351\227\255-\346\213\267\350\264\235-\346\214\211\344\270\213.png);}"));
        pushButtonConfirm = new QPushButton(widgetBox);
        pushButtonConfirm->setObjectName(QString::fromUtf8("pushButtonConfirm"));
        pushButtonConfirm->setGeometry(QRect(238, 330, 252, 56));
        QFont font3;
        font3.setPointSize(24);
        font3.setBold(false);
        font3.setWeight(50);
        pushButtonConfirm->setFont(font3);
        pushButtonConfirm->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(4, 185, 118);\n"
"border-radius:8px;"));
        pushButtonAccept = new QPushButton(widgetBox);
        pushButtonAccept->setObjectName(QString::fromUtf8("pushButtonAccept"));
        pushButtonAccept->setGeometry(QRect(70, 330, 252, 56));
        QFont font4;
        font4.setPointSize(24);
        pushButtonAccept->setFont(font4);
        pushButtonAccept->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(4, 185, 118);\n"
"border-radius:8px;"));
        pushButtonReject = new QPushButton(widgetBox);
        pushButtonReject->setObjectName(QString::fromUtf8("pushButtonReject"));
        pushButtonReject->setGeometry(QRect(406, 330, 252, 56));
        pushButtonReject->setFont(font4);
        pushButtonReject->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(165, 165, 165);\n"
"border-radius:8px;"));
        labelText = new QLabel(widgetBox);
        labelText->setObjectName(QString::fromUtf8("labelText"));
        labelText->setGeometry(QRect(0, 160, 725, 60));
        labelText->setFont(font2);
        labelText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        labelText->setAlignment(Qt::AlignCenter);
        pushButtonAccept_2 = new QPushButton(widgetBox);
        pushButtonAccept_2->setObjectName(QString::fromUtf8("pushButtonAccept_2"));
        pushButtonAccept_2->setGeometry(QRect(70, 330, 252, 56));
        pushButtonAccept_2->setFont(font4);
        pushButtonAccept_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(4, 185, 118);\n"
"border-radius:8px;"));
        pushButtonReject_2 = new QPushButton(widgetBox);
        pushButtonReject_2->setObjectName(QString::fromUtf8("pushButtonReject_2"));
        pushButtonReject_2->setGeometry(QRect(406, 330, 252, 56));
        pushButtonReject_2->setFont(font4);
        pushButtonReject_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(165, 165, 165);\n"
"border-radius:8px;"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelIdImage->setText(QString());
        labelMeitou->setText(QString());
        labelMeitouText->setText(QApplication::translate("MainWindow", "\346\227\205\345\256\242\351\232\217\350\272\253\350\241\214\346\235\216\345\274\200\345\214\205\347\263\273\347\273\237", nullptr));
        labelRightMeitou->setText(QString());
        labelRightMeitouText_1->setText(QApplication::translate("MainWindow", "RFID\347\274\226\345\217\267: ", nullptr));
        labelRightMeitouText_2->setText(QApplication::translate("MainWindow", "\350\241\214\346\235\216\346\241\206\347\274\226\345\217\267: ", nullptr));
        labelXImage->setText(QString());
        pushButtonNImage->setText(QString());
        pushButtonUpLoad->setText(QApplication::translate("MainWindow", "\346\217\220\343\200\200\344\272\244\343\200\200\344\270\212\343\200\200\344\274\240", nullptr));
        pushButtonClose->setText(QString());
        pushButtonConfirm->setText(QApplication::translate("MainWindow", "\347\241\256\343\200\200\350\256\244", nullptr));
        pushButtonAccept->setText(QApplication::translate("MainWindow", "\347\241\256\343\200\200\350\256\244\357\274\2103\357\274\211", nullptr));
        pushButtonReject->setText(QApplication::translate("MainWindow", "\345\217\226\343\200\200\346\266\210", nullptr));
        labelText->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244\346\217\220\344\272\244\344\270\212\344\274\240\350\257\245X\345\205\211\345\233\276\345\203\217\357\274\237", nullptr));
        pushButtonAccept_2->setText(QApplication::translate("MainWindow", "\347\241\256\343\200\200\345\256\232", nullptr));
        pushButtonReject_2->setText(QApplication::translate("MainWindow", "\345\217\226\343\200\200\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
