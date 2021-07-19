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
    QLabel *labelMeitou;
    QLabel *labelBackground;
    extendQLabel *labelXImage;
    QLabel *labelRightMeitou;
    QLabel *labelMeitouText;
    QLabel *labelRightMeitouText_1;
    QLabel *labelRightMeitouText_2;
    QPushButton *pushButtonNImage;
    QTableWidget *tableWidgetRight;
    QTableWidget *tableWidgetBottom;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        labelMeitou = new QLabel(centralwidget);
        labelMeitou->setObjectName(QString::fromUtf8("labelMeitou"));
        labelMeitou->setGeometry(QRect(0, 0, 1920, 65));
        QFont font;
        font.setPointSize(30);
        labelMeitou->setFont(font);
        labelMeitou->setStyleSheet(QString::fromUtf8("background-color: rgb(31, 46, 73);"));
        labelBackground = new QLabel(centralwidget);
        labelBackground->setObjectName(QString::fromUtf8("labelBackground"));
        labelBackground->setGeometry(QRect(0, 0, 1920, 1080));
        labelBackground->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 65, 109);"));
        labelXImage = new extendQLabel(centralwidget);
        labelXImage->setObjectName(QString::fromUtf8("labelXImage"));
        labelXImage->setGeometry(QRect(10, 75, 1262, 780));
        labelXImage->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 224, 229);"));
        labelRightMeitou = new QLabel(centralwidget);
        labelRightMeitou->setObjectName(QString::fromUtf8("labelRightMeitou"));
        labelRightMeitou->setGeometry(QRect(1282, 75, 628, 65));
        QFont font1;
        font1.setPointSize(25);
        labelRightMeitou->setFont(font1);
        labelRightMeitou->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 25, 42);"));
        labelMeitouText = new QLabel(centralwidget);
        labelMeitouText->setObjectName(QString::fromUtf8("labelMeitouText"));
        labelMeitouText->setGeometry(QRect(10, 0, 400, 65));
        labelMeitouText->setFont(font);
        labelMeitouText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        labelRightMeitouText_1 = new QLabel(centralwidget);
        labelRightMeitouText_1->setObjectName(QString::fromUtf8("labelRightMeitouText_1"));
        labelRightMeitouText_1->setGeometry(QRect(1292, 75, 351, 65));
        labelRightMeitouText_1->setFont(font1);
        labelRightMeitouText_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 252, 255);"));
        labelRightMeitouText_2 = new QLabel(centralwidget);
        labelRightMeitouText_2->setObjectName(QString::fromUtf8("labelRightMeitouText_2"));
        labelRightMeitouText_2->setGeometry(QRect(1660, 75, 250, 65));
        labelRightMeitouText_2->setFont(font1);
        labelRightMeitouText_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 252, 255);"));
        pushButtonNImage = new QPushButton(centralwidget);
        pushButtonNImage->setObjectName(QString::fromUtf8("pushButtonNImage"));
        pushButtonNImage->setGeometry(QRect(1010, 651, 252, 194));
        pushButtonNImage->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 102, 105);\n"
"border: 0;\n"
"image: 0;"));
        tableWidgetRight = new QTableWidget(centralwidget);
        tableWidgetRight->setObjectName(QString::fromUtf8("tableWidgetRight"));
        tableWidgetRight->setGeometry(QRect(1282, 145, 628, 710));
        tableWidgetRight->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background-color: rgb(1, 65, 109);"));
        tableWidgetRight->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidgetBottom = new QTableWidget(centralwidget);
        tableWidgetBottom->setObjectName(QString::fromUtf8("tableWidgetBottom"));
        tableWidgetBottom->setGeometry(QRect(5, 865, 1905, 205));
        tableWidgetBottom->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background-color: rgb(1, 65, 109);"));
        MainWindow->setCentralWidget(centralwidget);
        labelBackground->raise();
        labelMeitou->raise();
        labelXImage->raise();
        labelRightMeitou->raise();
        labelMeitouText->raise();
        labelRightMeitouText_1->raise();
        labelRightMeitouText_2->raise();
        pushButtonNImage->raise();
        tableWidgetRight->raise();
        tableWidgetBottom->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelMeitou->setText(QString());
        labelBackground->setText(QString());
        labelXImage->setText(QString());
        labelRightMeitou->setText(QString());
        labelMeitouText->setText(QApplication::translate("MainWindow", "\346\227\205\345\256\242\351\232\217\350\272\253\350\241\214\346\235\216\345\274\200\345\214\205\347\263\273\347\273\237", nullptr));
        labelRightMeitouText_1->setText(QApplication::translate("MainWindow", "RFID\347\274\226\345\217\267: ", nullptr));
        labelRightMeitouText_2->setText(QApplication::translate("MainWindow", "\350\241\214\346\235\216\346\241\206\347\274\226\345\217\267: ", nullptr));
        pushButtonNImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
