#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QPalette>

/******************************************************************************
 *
 * @file       main.cpp
 * @brief      主入口文件，包含登录验证逻辑，并强制设置白色主题
 *
 * @author     壹加贰等于Sam
 * @date       2026/04/27
 *****************************************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 强制使用 Fusion 风格并设置明亮调色板，防止跟随系统深色模式
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::AlternateBase, QColor(233, 231, 227));
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Highlight, QColor(76, 163, 224));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);
    a.setPalette(lightPalette);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GeoQt-Client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
