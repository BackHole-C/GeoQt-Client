#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

/**
 * @brief LoginDialog 类提供了一个简单的登录界面
 */
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);

private slots:
    void handleLogin();

private:
    QLineEdit *m_passwordEdit;
    QPushButton *m_loginButton;
};

#endif // LOGINDIALOG_H
