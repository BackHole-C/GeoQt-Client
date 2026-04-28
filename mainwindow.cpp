#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mapcanvas.h"
#include <QDockWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLayout()
{
    // 1. 设置主窗口标题和图标
    setWindowTitle("GeoQt-Client (极地地理信息系统)");
    setWindowIcon(QIcon(":/res/logo.ico"));
    resize(1200, 800);

    // 2. 初始化中心挂件：地图画布
    m_mapCanvas = new MapCanvas(this);
    setCentralWidget(m_mapCanvas);

    // 3. 初始化左侧停靠面板 (QDockWidget)
    m_dockPanel = new QDockWidget("业务功能控制面板", this);
    m_dockPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dockPanel->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    // 面板内部容器
    QWidget *dockContent = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(dockContent);

    QLabel *tipLabel = new QLabel("此处放置具体业务逻辑：\n- POI 搜索\n- 路径规划\n- 图元管理", this);
    tipLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(tipLabel);
    layout->addStretch(); // 弹簧将内容推送到上方

    m_dockPanel->setWidget(dockContent);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockPanel);
}
