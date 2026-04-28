#include "mapcanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

MapCanvas::MapCanvas(QWidget *parent)
    : QWidget(parent)
{
    // 设置背景色以区分画布区域
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color: #f0f0f0;");
}

void MapCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制临时占位文字记录地图状态
    painter.setPen(Qt::gray);
    painter.drawText(rect(), Qt::AlignCenter, "地图渲染画布 (MapCanvas)\n等待瓦片数据加载...");
}

void MapCanvas::mousePressEvent(QMouseEvent *event)
{
    // 处理地图拖拽开始
}

void MapCanvas::mouseMoveEvent(QMouseEvent *event)
{
    // 处理地图平移
}

void MapCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    // 处理地图拖拽结束
}

void MapCanvas::wheelEvent(QWheelEvent *event)
{
    // 处理地图缩放
}
