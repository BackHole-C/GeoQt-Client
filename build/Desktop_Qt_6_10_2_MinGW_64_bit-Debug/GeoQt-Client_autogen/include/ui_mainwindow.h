/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mapcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    MapCanvas *mapView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *akEdit;
    QPushButton *initBtn;
    QLabel *label_2;
    QLabel *coordLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        mapView = new MapCanvas(centralwidget);
        mapView->setObjectName("mapView");

        horizontalLayout->addWidget(mapView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName("dockWidget");
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(dockWidgetContents);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        akEdit = new QLineEdit(dockWidgetContents);
        akEdit->setObjectName("akEdit");

        verticalLayout->addWidget(akEdit);

        initBtn = new QPushButton(dockWidgetContents);
        initBtn->setObjectName("initBtn");
        initBtn->setStyleSheet(QString::fromUtf8("background-color: #0078d4; color: white; height: 30px; font-weight: bold;"));

        verticalLayout->addWidget(initBtn);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        coordLabel = new QLabel(dockWidgetContents);
        coordLabel->setObjectName("coordLabel");
        coordLabel->setStyleSheet(QString::fromUtf8("color: #333; font-family: Consolas;"));

        verticalLayout->addWidget(coordLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "GeoQt-Client (\346\236\201\345\234\260\345\234\260\347\220\206\344\277\241\346\201\257\347\263\273\347\273\237)", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\270\232\345\212\241\345\212\237\350\203\275\346\216\247\345\210\266\351\235\242\346\235\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\231\276\345\272\246\345\234\260\345\233\276\345\274\200\346\224\276\345\271\263\345\217\260 AK:", nullptr));
        akEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204 AK \345\257\206\351\222\245...", nullptr));
        initBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\345\234\260\345\233\276", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\344\270\255\345\277\203\347\202\271\345\235\220\346\240\207:", nullptr));
        coordLabel->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\345\210\235\345\247\213\345\214\226...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
