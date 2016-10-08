/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Oct 8 08:12:17 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "visualizacao.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionConfigure;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pbStartStop;
    Visualizacao *wVisualizacao;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QRadioButton *rbYellowColor;
    QRadioButton *rbBlueColor;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QGroupBox *groupBox;
    QRadioButton *rbLeftColor;
    QRadioButton *rbRightColor;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_referee;
    QSpinBox *sbIDGoleiro;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbStartStop = new QPushButton(centralwidget);
        pbStartStop->setObjectName(QString::fromUtf8("pbStartStop"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbStartStop->sizePolicy().hasHeightForWidth());
        pbStartStop->setSizePolicy(sizePolicy);
        pbStartStop->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(pbStartStop, 0, 0, 1, 1);

        wVisualizacao = new Visualizacao(centralwidget);
        wVisualizacao->setObjectName(QString::fromUtf8("wVisualizacao"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(wVisualizacao->sizePolicy().hasHeightForWidth());
        wVisualizacao->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(wVisualizacao, 1, 0, 1, 5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(label_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(170, 0));
        rbYellowColor = new QRadioButton(groupBox_3);
        rbYellowColor->setObjectName(QString::fromUtf8("rbYellowColor"));
        rbYellowColor->setGeometry(QRect(79, 1, 76, 22));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rbYellowColor->sizePolicy().hasHeightForWidth());
        rbYellowColor->setSizePolicy(sizePolicy3);
        rbYellowColor->setChecked(true);
        rbBlueColor = new QRadioButton(groupBox_3);
        rbBlueColor->setObjectName(QString::fromUtf8("rbBlueColor"));
        rbBlueColor->setGeometry(QRect(11, 3, 61, 20));
        sizePolicy3.setHeightForWidth(rbBlueColor->sizePolicy().hasHeightForWidth());
        rbBlueColor->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(groupBox_3);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(label);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(170, 0));
        rbLeftColor = new QRadioButton(groupBox);
        rbLeftColor->setObjectName(QString::fromUtf8("rbLeftColor"));
        rbLeftColor->setGeometry(QRect(70, 0, 61, 22));
        sizePolicy3.setHeightForWidth(rbLeftColor->sizePolicy().hasHeightForWidth());
        rbLeftColor->setSizePolicy(sizePolicy3);
        rbLeftColor->setMinimumSize(QSize(0, 0));
        rbLeftColor->setChecked(true);
        rbRightColor = new QRadioButton(groupBox);
        rbRightColor->setObjectName(QString::fromUtf8("rbRightColor"));
        rbRightColor->setGeometry(QRect(3, 1, 71, 21));
        sizePolicy.setHeightForWidth(rbRightColor->sizePolicy().hasHeightForWidth());
        rbRightColor->setSizePolicy(sizePolicy);
        rbRightColor->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(groupBox);


        gridLayout->addLayout(verticalLayout_2, 0, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(label_3);

        label_referee = new QLabel(centralwidget);
        label_referee->setObjectName(QString::fromUtf8("label_referee"));

        verticalLayout_3->addWidget(label_referee);

        sbIDGoleiro = new QSpinBox(centralwidget);
        sbIDGoleiro->setObjectName(QString::fromUtf8("sbIDGoleiro"));
        sizePolicy.setHeightForWidth(sbIDGoleiro->sizePolicy().hasHeightForWidth());
        sbIDGoleiro->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(sbIDGoleiro);


        gridLayout->addLayout(verticalLayout_3, 0, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionConnect);
        toolBar->addAction(actionConfigure);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        actionConfigure->setText(QApplication::translate("MainWindow", "Configure", 0, QApplication::UnicodeUTF8));
        pbStartStop->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Team Color:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        rbYellowColor->setText(QApplication::translate("MainWindow", "Yellow", 0, QApplication::UnicodeUTF8));
        rbBlueColor->setText(QApplication::translate("MainWindow", "Blue", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Team Side:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        rbLeftColor->setText(QApplication::translate("MainWindow", "Left", 0, QApplication::UnicodeUTF8));
        rbRightColor->setText(QApplication::translate("MainWindow", "Right", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "ID Goleiro:", 0, QApplication::UnicodeUTF8));
        label_referee->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
