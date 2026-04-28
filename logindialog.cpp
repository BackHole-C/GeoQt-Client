#include "logindialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("系统登录 - GeoQt-Client");
    setFixedSize(300, 150);
    setWindowIcon(QIcon(":/res/logo.ico"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("请输入管理密码进入系统", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("请输入密码...");
    mainLayout->addWidget(m_passwordEdit);

    m_loginButton = new QPushButton("登录", this);
    m_loginButton->setDefault(true);
    mainLayout->addWidget(m_loginButton);

    connect(m_loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);
}

void LoginDialog::handleLogin()
{
    // 这里设置一个简单的静态密码，实际项目中可以从配置或服务器验证
    const QString correctPassword = "admin";

    if (m_passwordEdit->text() == correctPassword)
    {
        accept(); // 关闭对话框并返回 QDialog::Accepted
    }
    else
    {
        QMessageBox::warning(this, "错误", "密码不正确，请重新输入！");
        m_passwordEdit->clear();
        m_passwordEdit->setFocus();
    }
}
