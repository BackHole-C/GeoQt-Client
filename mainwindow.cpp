#include "mainwindow.h"
#include "mapcanvas.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置基础窗口属性
    setWindowIcon(QIcon(":/res/logo.ico"));
    resize(1200, 800);

    // 绑定 UI 中的信号（通过 ui-> 访问）
    connect(ui->initBtn, &QPushButton::clicked, this, &MainWindow::onInitMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInitMap()
{
    QString ak = ui->akEdit->text().trimmed();
    if (ak.isEmpty())
    {
        ui->coordLabel->setText("<font color='red'>错误：AK 不能为空</font>");
        return;
    }

    // 使用 MapCanvas 模式初始化地图
    ui->mapView->initMapEngine(ak);

    // 更新界面坐标显示
    QPointF coord = ui->mapView->centerCoordinate();
    ui->coordLabel->setText(QString("经度: %1\n纬度: %2").arg(coord.x()).arg(coord.y()));
}
