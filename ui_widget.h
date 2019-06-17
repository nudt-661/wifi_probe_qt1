/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextBrowser *macTextBrowser;
    QTextBrowser *wifiTextBrowser;
    QTextBrowser *aptextBrowser;
    QLabel *wifi;
    QLabel *device;
    QGraphicsView *graphicsView;
    QComboBox *ssidComboBox;
    QTextBrowser *orgTextBrowser;
    QLabel *text;
    QComboBox *macComboBox;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(544, 406);
        macTextBrowser = new QTextBrowser(Widget);
        macTextBrowser->setObjectName(QStringLiteral("macTextBrowser"));
        macTextBrowser->setGeometry(QRect(272, 44, 256, 192));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(macTextBrowser->sizePolicy().hasHeightForWidth());
        macTextBrowser->setSizePolicy(sizePolicy);
        macTextBrowser->setSizeIncrement(QSize(10, 10));
        macTextBrowser->setStyleSheet(QStringLiteral("font: 75 11pt \"Source Code Pro\";"));
        wifiTextBrowser = new QTextBrowser(Widget);
        wifiTextBrowser->setObjectName(QStringLiteral("wifiTextBrowser"));
        wifiTextBrowser->setGeometry(QRect(10, 44, 256, 161));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(wifiTextBrowser->sizePolicy().hasHeightForWidth());
        wifiTextBrowser->setSizePolicy(sizePolicy1);
        wifiTextBrowser->setMinimumSize(QSize(0, 0));
        wifiTextBrowser->setMaximumSize(QSize(16777215, 16777215));
        wifiTextBrowser->setSizeIncrement(QSize(10, 10));
        wifiTextBrowser->setStyleSheet(QStringLiteral("font: 75 11pt \"Source Code Pro\";"));
        aptextBrowser = new QTextBrowser(Widget);
        aptextBrowser->setObjectName(QStringLiteral("aptextBrowser"));
        aptextBrowser->setGeometry(QRect(10, 280, 256, 41));
        sizePolicy1.setHeightForWidth(aptextBrowser->sizePolicy().hasHeightForWidth());
        aptextBrowser->setSizePolicy(sizePolicy1);
        aptextBrowser->setMinimumSize(QSize(0, 0));
        aptextBrowser->setSizeIncrement(QSize(10, 10));
        aptextBrowser->setStyleSheet(QStringLiteral("font: 75 11pt \"Source Code Pro\";"));
        wifi = new QLabel(Widget);
        wifi->setObjectName(QStringLiteral("wifi"));
        wifi->setGeometry(QRect(10, 10, 251, 28));
        device = new QLabel(Widget);
        device->setObjectName(QStringLiteral("device"));
        device->setGeometry(QRect(270, 10, 251, 28));
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(272, 242, 256, 111));
        graphicsView->setSizeIncrement(QSize(10, 10));
        ssidComboBox = new QComboBox(Widget);
        ssidComboBox->setObjectName(QStringLiteral("ssidComboBox"));
        ssidComboBox->setGeometry(QRect(10, 240, 251, 35));
        sizePolicy1.setHeightForWidth(ssidComboBox->sizePolicy().hasHeightForWidth());
        ssidComboBox->setSizePolicy(sizePolicy1);
        ssidComboBox->setMinimumSize(QSize(0, 0));
        ssidComboBox->setStyleSheet(QStringLiteral("font: 75 11pt \"Source Code Pro\";"));
        orgTextBrowser = new QTextBrowser(Widget);
        orgTextBrowser->setObjectName(QStringLiteral("orgTextBrowser"));
        orgTextBrowser->setGeometry(QRect(10, 330, 256, 61));
        orgTextBrowser->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QStringLiteral("Source Code Pro"));
        font.setPointSize(11);
        orgTextBrowser->setFont(font);
        text = new QLabel(Widget);
        text->setObjectName(QStringLiteral("text"));
        text->setGeometry(QRect(10, 210, 261, 31));
        macComboBox = new QComboBox(Widget);
        macComboBox->setObjectName(QStringLiteral("macComboBox"));
        macComboBox->setGeometry(QRect(270, 360, 261, 29));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        macTextBrowser->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Source Code Pro'; font-size:11pt; font-weight:72; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'PibotoLt'; font-size:16pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        wifiTextBrowser->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Source Code Pro'; font-size:11pt; font-weight:72; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'PibotoLt'; font-size:14pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        wifi->setText(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Piboto Light'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; color:#000000;\">\347\203\255\347\202\271\345\220\215\347\247\260</span></p></body></html>", Q_NULLPTR));
        device->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-family:'arial'; font-size:10pt; color:#000000;\">\350\277\236\346\216\245\345\210\260\347\203\255\347\202\271\347\232\204\350\256\276\345\244\207</span></p></body></html>", Q_NULLPTR));
        text->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\351\200\211\346\213\251\347\203\255\347\202\271\345\220\215\347\247\260\346\237\245\350\257\242\350\277\236\346\216\245\345\210\260\347\203\255\347\202\271\347\232\204\350\256\276\345\244\207</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
