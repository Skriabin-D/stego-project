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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QHBoxLayout *selectionLayout;
    QLabel *labelMode;
    QComboBox *comboMode;
    QSpacerItem *horizontalSpacer;
    QLabel *labelMethod;
    QComboBox *comboMethod;
    QPushButton *buttonLoadImage;
    QHBoxLayout *previewLayout;
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
        MainWindow->resize(1200, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        selectionLayout = new QHBoxLayout();
        selectionLayout->setObjectName("selectionLayout");
        labelMode = new QLabel(centralwidget);
        labelMode->setObjectName("labelMode");

        selectionLayout->addWidget(labelMode);

        comboMode = new QComboBox(centralwidget);
        comboMode->addItem(QString());
        comboMode->addItem(QString());
        comboMode->setObjectName("comboMode");

        selectionLayout->addWidget(comboMode);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        selectionLayout->addItem(horizontalSpacer);

        labelMethod = new QLabel(centralwidget);
        labelMethod->setObjectName("labelMethod");

        selectionLayout->addWidget(labelMethod);

        comboMethod = new QComboBox(centralwidget);
        comboMethod->addItem(QString());
        comboMethod->addItem(QString());
        comboMethod->setObjectName("comboMethod");

        selectionLayout->addWidget(comboMethod);


        verticalLayout->addLayout(selectionLayout);

        buttonLoadImage = new QPushButton(centralwidget);
        buttonLoadImage->setObjectName("buttonLoadImage");

        verticalLayout->addWidget(buttonLoadImage);

        previewLayout = new QHBoxLayout();
        previewLayout->setObjectName("previewLayout");
        labelOriginal = new QLabel(centralwidget);
        labelOriginal->setObjectName("labelOriginal");

        previewLayout->addWidget(labelOriginal);

        labelResult = new QLabel(centralwidget);
        labelResult->setObjectName("labelResult");

        previewLayout->addWidget(labelResult);


        verticalLayout->addLayout(previewLayout);

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
        labelMode->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274:", nullptr));
        comboMode->setItemText(0, QCoreApplication::translate("MainWindow", "Embed", nullptr));
        comboMode->setItemText(1, QCoreApplication::translate("MainWindow", "Extract", nullptr));

        labelMethod->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264:", nullptr));
        comboMethod->setItemText(0, QCoreApplication::translate("MainWindow", "PVD", nullptr));
        comboMethod->setItemText(1, QCoreApplication::translate("MainWindow", "LSB-DCT", nullptr));

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
