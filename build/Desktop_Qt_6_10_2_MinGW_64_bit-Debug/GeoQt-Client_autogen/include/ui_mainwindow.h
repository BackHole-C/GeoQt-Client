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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *akLabel;
    QLineEdit *akEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lngLabel;
    QDoubleSpinBox *lngEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *latLabel;
    QDoubleSpinBox *latEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *zoomLabel;
    QSpinBox *zoomEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *staLabel;
    QLabel *coordLabel;
    QPushButton *initBtn;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QComboBox *mtypeBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QComboBox *comboBox;
    QPushButton *mtypeBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1091, 674);
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
        menubar->setGeometry(QRect(0, 0, 1091, 20));
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
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, -1, 8, 0);
        label = new QLabel(dockWidgetContents);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(8, -1, -1, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, -1, -1);
        akLabel = new QLabel(dockWidgetContents);
        akLabel->setObjectName("akLabel");
        akLabel->setMinimumSize(QSize(40, 0));
        akLabel->setMaximumSize(QSize(40, 40));

        horizontalLayout_3->addWidget(akLabel);

        akEdit = new QLineEdit(dockWidgetContents);
        akEdit->setObjectName("akEdit");
        akEdit->setMinimumSize(QSize(0, 0));
        akEdit->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(akEdit);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, -1, -1, -1);
        lngLabel = new QLabel(dockWidgetContents);
        lngLabel->setObjectName("lngLabel");
        lngLabel->setMaximumSize(QSize(40, 40));

        horizontalLayout_4->addWidget(lngLabel);

        lngEdit = new QDoubleSpinBox(dockWidgetContents);
        lngEdit->setObjectName("lngEdit");
        lngEdit->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        lngEdit->setDecimals(4);
        lngEdit->setMaximum(180.000000000000000);
        lngEdit->setValue(112.924000000000007);

        horizontalLayout_4->addWidget(lngEdit);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        latLabel = new QLabel(dockWidgetContents);
        latLabel->setObjectName("latLabel");
        latLabel->setMaximumSize(QSize(40, 40));

        horizontalLayout_5->addWidget(latLabel);

        latEdit = new QDoubleSpinBox(dockWidgetContents);
        latEdit->setObjectName("latEdit");
        latEdit->setDecimals(4);
        latEdit->setMaximum(180.000000000000000);
        latEdit->setValue(28.174499999999998);

        horizontalLayout_5->addWidget(latEdit);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, -1, -1, -1);
        zoomLabel = new QLabel(dockWidgetContents);
        zoomLabel->setObjectName("zoomLabel");
        zoomLabel->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(zoomLabel);

        zoomEdit = new QSpinBox(dockWidgetContents);
        zoomEdit->setObjectName("zoomEdit");
        zoomEdit->setMaximum(20);
        zoomEdit->setValue(12);

        horizontalLayout_7->addWidget(zoomEdit);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, -1, 0);
        staLabel = new QLabel(dockWidgetContents);
        staLabel->setObjectName("staLabel");
        staLabel->setMinimumSize(QSize(0, 25));
        staLabel->setMaximumSize(QSize(40, 25));

        horizontalLayout_6->addWidget(staLabel);

        coordLabel = new QLabel(dockWidgetContents);
        coordLabel->setObjectName("coordLabel");
        coordLabel->setMinimumSize(QSize(0, 25));
        coordLabel->setMaximumSize(QSize(16777215, 25));
        coordLabel->setStyleSheet(QString::fromUtf8("color: #333; font-family: Consolas;\n"
"background-color: rgb(255, 255, 255);"));
        coordLabel->setTextFormat(Qt::TextFormat::AutoText);
        coordLabel->setScaledContents(false);
        coordLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        coordLabel->setMargin(5);

        horizontalLayout_6->addWidget(coordLabel);


        verticalLayout_3->addLayout(horizontalLayout_6);

        initBtn = new QPushButton(dockWidgetContents);
        initBtn->setObjectName("initBtn");
        initBtn->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255); color: rgb(0, 0, 0); height: 30px; font-weight: bold;"));
        initBtn->setAutoDefault(false);

        verticalLayout_3->addWidget(initBtn);


        verticalLayout_2->addLayout(verticalLayout_3);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(8, -1, -1, -1);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, -1, -1, -1);
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(40, 0));
        label_3->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_8->addWidget(label_3);

        mtypeBox = new QComboBox(dockWidgetContents);
        mtypeBox->addItem(QString());
        mtypeBox->addItem(QString());
        mtypeBox->addItem(QString());
        mtypeBox->setObjectName("mtypeBox");

        horizontalLayout_8->addWidget(mtypeBox);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(40, 0));
        label_4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_9->addWidget(label_4);

        comboBox = new QComboBox(dockWidgetContents);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_9->addWidget(comboBox);


        verticalLayout_4->addLayout(horizontalLayout_9);

        mtypeBtn = new QPushButton(dockWidgetContents);
        mtypeBtn->setObjectName("mtypeBtn");

        verticalLayout_4->addWidget(mtypeBtn);


        verticalLayout_2->addLayout(verticalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_2);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "GeoQt-Client (\346\236\201\345\234\260\345\234\260\347\220\206\344\277\241\346\201\257\347\263\273\347\273\237)", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\217\234\345\215\225", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\234\260\345\233\276\345\210\235\345\247\213\345\214\226", nullptr));
        akLabel->setText(QCoreApplication::translate("MainWindow", "AK", nullptr));
        akEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204 AK \345\257\206\351\222\245...", nullptr));
        lngLabel->setText(QCoreApplication::translate("MainWindow", "Lng", nullptr));
        latLabel->setText(QCoreApplication::translate("MainWindow", "Lat", nullptr));
        zoomLabel->setText(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
        staLabel->setText(QCoreApplication::translate("MainWindow", "State", nullptr));
        coordLabel->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\345\210\235\345\247\213\345\214\226...", nullptr));
        initBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\345\234\260\345\233\276", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\234\260\345\233\276\347\261\273\345\236\213", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Map", nullptr));
        mtypeBox->setItemText(0, QCoreApplication::translate("MainWindow", "Nomal", nullptr));
        mtypeBox->setItemText(1, QCoreApplication::translate("MainWindow", "Satellite", nullptr));
        mtypeBox->setItemText(2, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "Layer", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Traffic", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "HeatMap", nullptr));

        mtypeBtn->setText(QCoreApplication::translate("MainWindow", "Switch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
