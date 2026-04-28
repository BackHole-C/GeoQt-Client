#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

/******************************************************************************
 *
 * @file       main.cpp
 * @brief      主入口文件，包含登录验证逻辑
 *
 * @author     壹加贰等于Sam
 * @date       2026/04/27
 *****************************************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "GeoQt-Client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }

    // 1. 显示登录对话框
    LoginDialog login;
    if (login.exec() != QDialog::Accepted)
    {
        // 如果用户关闭或取消登录，则退出程序
        return 0;
    }

    // 2. 验证通过，显示主窗口
    MainWindow w;
    w.show();
    return QApplication::exec();
}
