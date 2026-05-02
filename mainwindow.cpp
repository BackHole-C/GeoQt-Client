#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QMessageBox>
#include <QIcon>
#include <QStyleOption>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 修复 Logo：根据 resources.qrc，路径应该是 :/res/logo.ico
    setWindowIcon(QIcon(":/res/logo.ico"));

    // 2. UI 综合美化
    ui->dockWidget->setStyleSheet(
        "QDockWidget { border: none; }"
        "QWidget#dockWidgetContents { background-color: #f5f5f7; border-right: 1px solid #d2d2d7; }"
        "QPushButton { background-color: #ffffff; border: 1px solid #d2d2d7; border-radius: 4px; padding: 5px; min-height: 25px; color: #333333; }"
        "QPushButton:hover { background-color: #e8e8ed; }"
        "QLineEdit { border: 1px solid #d2d2d7; border-radius: 4px; padding: 3px; background: white; color: #333333; }"
        "QComboBox { border: 1px solid #d2d2d7; border-radius: 4px; padding: 3px; background: white; color: #333333; }"
        "QComboBox QAbstractItemView { background-color: white; color: #333333; selection-background-color: #0078d4; selection-color: white; border: 1px solid #d2d2d7; }"
        "QLabel { color: #333333; font-weight: bold; }");

    // 3. 布局调整
    ui->horizontalLayout->setContentsMargins(10, 10, 10, 10);
    ui->horizontalLayout->setSpacing(5);

    // 4. 地图区域外部容器样式（确保在 mapcanvas 内部绘图之前也有一层灰色底色）
    ui->mapView->setStyleSheet("background-color: #dcdcdc; border-radius: 2px;");

    loadConfig();

    connect(ui->initBtn, &QPushButton::clicked, this, &MainWindow::onInitMap);

    connect(ui->mtypeBtn, &QPushButton::clicked, this, [this]()
            {
        int index = ui->mtypeBox->currentIndex();
        if (index == 0) ui->mapView->setMapType(MapCanvas::Normal);
        else if (index == 1) ui->mapView->setMapType(MapCanvas::Satellite);
        else if (index == 2) ui->mapView->setMapType(MapCanvas::None);
        
        int layerIndex = ui->comboBox->currentIndex();
        ui->mapView->setTrafficEnabled(layerIndex == 1);
        ui->mapView->setHeatMapEnabled(layerIndex == 2); });

    // 监听纬度/经度/缩放的变化
    connect(ui->lngEdit, &QDoubleSpinBox::editingFinished, this, [this]()
            { ui->mapView->setCenterCoordinate(QPointF(ui->lngEdit->value(), ui->latEdit->value())); });
    connect(ui->latEdit, &QDoubleSpinBox::editingFinished, this, [this]()
            { ui->mapView->setCenterCoordinate(QPointF(ui->lngEdit->value(), ui->latEdit->value())); });
    connect(ui->zoomEdit, &QSpinBox::editingFinished, this, [this]()
            { ui->mapView->setZoomLevel(ui->zoomEdit->value()); });
}

MainWindow::~MainWindow()
{
    saveConfig();
    delete ui;
}

void MainWindow::onInitMap()
{
    QString ak = ui->akEdit->text().trimmed();
    if (ak.isEmpty())
    {
        QMessageBox::warning(this, "错误", "请输入百度地图浏览器端 AK");
        return;
    }
    ui->mapView->setCenterCoordinate(QPointF(ui->lngEdit->value(), ui->latEdit->value()));
    ui->mapView->setZoomLevel(ui->zoomEdit->value());
    ui->mapView->initMapEngine(ak);
    ui->coordLabel->setText("地图引擎已启动");
}

void MainWindow::loadConfig()
{
    // 使用 QSettings 读取配置文件。
    QSettings settings("config.ini", QSettings::IniFormat);

    ui->akEdit->setText(settings.value("Map/AK").toString());

    // 恢复正确的默认值：112.9240 ，28.1745
    ui->lngEdit->setValue(settings.value("Map/Lng", 112.9240).toDouble());
    ui->latEdit->setValue(settings.value("Map/Lat", 28.1745).toDouble());
    ui->zoomEdit->setValue(settings.value("Map/Zoom", 12).toInt());
}

void MainWindow::saveConfig()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("Map/AK", ui->akEdit->text());
    settings.setValue("Map/Lng", ui->lngEdit->value());
    settings.setValue("Map/Lat", ui->latEdit->value());
    settings.setValue("Map/Zoom", ui->zoomEdit->value());
}
