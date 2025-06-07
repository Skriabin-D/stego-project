/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *modeLayout;
    QRadioButton *radioEmbed;
    QRadioButton *radioExtract;
    QHBoxLayout *methodLayout;
    QRadioButton *radioMethodPVD;
    QRadioButton *radioLSB;
    QPushButton *buttonLoadImage;
    QHBoxLayout *hboxLayout;
    QLabel *labelOriginal;
    QLabel *labelResult;
    QLabel *labelMessage;
    QLineEdit *lineMessage;
    QLabel *labelBitCount;
    QSpinBox *spinNumBits;
    QPushButton *buttonProcess;
    QTextEdit *textOutput;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        modeLayout = new QHBoxLayout();
        modeLayout->setObjectName("modeLayout");
        radioEmbed = new QRadioButton(centralwidget);
        radioEmbed->setObjectName("radioEmbed");
        radioEmbed->setChecked(true);

        modeLayout->addWidget(radioEmbed);

        radioExtract = new QRadioButton(centralwidget);
        radioExtract->setObjectName("radioExtract");

        modeLayout->addWidget(radioExtract);


        verticalLayout->addLayout(modeLayout);

        methodLayout = new QHBoxLayout();
        methodLayout->setObjectName("methodLayout");
        radioMethodPVD = new QRadioButton(centralwidget);
        radioMethodPVD->setObjectName("radioMethodPVD");
        radioMethodPVD->setChecked(true);

        methodLayout->addWidget(radioMethodPVD);

        radioLSB = new QRadioButton(centralwidget);
        radioLSB->setObjectName("radioLSB");

        methodLayout->addWidget(radioLSB);


        verticalLayout->addLayout(methodLayout);

        buttonLoadImage = new QPushButton(centralwidget);
        buttonLoadImage->setObjectName("buttonLoadImage");

        verticalLayout->addWidget(buttonLoadImage);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        labelOriginal = new QLabel(centralwidget);
        labelOriginal->setObjectName("labelOriginal");

        hboxLayout->addWidget(labelOriginal);

        labelResult = new QLabel(centralwidget);
        labelResult->setObjectName("labelResult");

        hboxLayout->addWidget(labelResult);


        verticalLayout->addLayout(hboxLayout);

        labelMessage = new QLabel(centralwidget);
        labelMessage->setObjectName("labelMessage");

        verticalLayout->addWidget(labelMessage);

        lineMessage = new QLineEdit(centralwidget);
        lineMessage->setObjectName("lineMessage");

        verticalLayout->addWidget(lineMessage);

        labelBitCount = new QLabel(centralwidget);
        labelBitCount->setObjectName("labelBitCount");

        verticalLayout->addWidget(labelBitCount);

        spinNumBits = new QSpinBox(centralwidget);
        spinNumBits->setObjectName("spinNumBits");
        spinNumBits->setMinimum(1);
        spinNumBits->setMaximum(1000000);

        verticalLayout->addWidget(spinNumBits);

        buttonProcess = new QPushButton(centralwidget);
        buttonProcess->setObjectName("buttonProcess");

        verticalLayout->addWidget(buttonProcess);

        textOutput = new QTextEdit(centralwidget);
        textOutput->setObjectName("textOutput");
        textOutput->setReadOnly(true);

        verticalLayout->addWidget(textOutput);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\265\320\263\320\260\320\275\320\276\320\263\321\200\320\260\321\204\320\270\321\217", nullptr));
        radioEmbed->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\321\200\320\260\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
        radioExtract->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\262\320\273\320\265\321\207\320\265\320\275\320\270\320\265", nullptr));
        radioMethodPVD->setText(QCoreApplication::translate("MainWindow", "PVD", nullptr));
        radioLSB->setText(QCoreApplication::translate("MainWindow", "LSB-DCT", nullptr));
        buttonLoadImage->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        labelOriginal->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\205\320\276\320\264\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        labelResult->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        labelMessage->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265:", nullptr));
        labelBitCount->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\270\321\202:", nullptr));
        buttonProcess->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\321\200\320\276\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
