#include "mapcanvas.h"
#include "tiledownloader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtMath>
#include <QDebug>

MapCanvas::MapCanvas(QWidget *parent) : QWidget(parent)
{
    m_downloader = new TileDownloader(this);
    connect(m_downloader, &TileDownloader::tileDownloaded, this, [this](int x, int y, int z, const QString &style, const QPixmap &pix)
            {
        // 构建当前要求的 style
        QString currentStyle = (m_mapType == Satellite) ? "sate" : (m_mapType == None ? "none" : "pl");
        if (m_trafficEnabled) currentStyle += "_traf";
        if (m_heatMapEnabled) currentStyle += "_heat";

        // 核心机制：只有当下载好的瓦片类型与当前地图状态完全匹配时，才存入缓存
        // 这样可以防止切换类型时，旧请求缓慢返回导致的图层错乱
        if (z == m_zoomLevel && style == currentStyle) {
            QString key = QString("%1_%2_%3_%4").arg(style).arg(z).arg(x).arg(y);
            m_tileCache[key] = pix;
            update();
        } });
}

void MapCanvas::initMapEngine(const QString &ak)
{
    m_ak = ak;
    m_isInitialized = true;
    m_tileCache.clear();
    requestVisibleTiles();
    update();
}

void MapCanvas::setCenterCoordinate(const QPointF &coord)
{
    if (m_centerCoord != coord)
    {
        m_centerCoord = coord;
        // 注意：平移不一定需要 clearCache，为了性能可以保留
        requestVisibleTiles();
        update();
    }
}

void MapCanvas::setZoomLevel(int level)
{
    int newLevel = qBound(3, level, 19);
    if (m_zoomLevel != newLevel)
    {
        m_zoomLevel = newLevel;
        m_tileCache.clear();
        requestVisibleTiles();
        update();
    }
}

void MapCanvas::setMapType(MapType type)
{
    if (m_mapType != type)
    {
        m_mapType = type;
        m_tileCache.clear(); // 切换类型必须清理，防止视觉残留
        requestVisibleTiles();
        update();
    }
}

void MapCanvas::setTrafficEnabled(bool enabled)
{
    if (m_trafficEnabled != enabled)
    {
        m_trafficEnabled = enabled;
        m_tileCache.clear();
        requestVisibleTiles();
        update();
    }
}

void MapCanvas::setHeatMapEnabled(bool enabled)
{
    if (m_heatMapEnabled != enabled)
    {
        m_heatMapEnabled = enabled;
        m_tileCache.clear();
        requestVisibleTiles();
        update();
    }
}

void MapCanvas::requestVisibleTiles()
{
    if (!m_isInitialized || m_ak.isEmpty())
        return;

    // 百度坐标计算逻辑
    double mcX = m_centerCoord.x() * 111319.49077777778;
    double mcY = qLn(qTan((m_centerCoord.y() + 90.0) * M_PI / 360.0)) * 6378137.0;
    double zoomFactor = qPow(2.0, 18 - m_zoomLevel);

    int centerTileX = qFloor(mcX / (256.0 * zoomFactor));
    int centerTileY = qFloor(mcY / (256.0 * zoomFactor));

    int rangeX = (width() / 256) / 2 + 2;
    int rangeY = (height() / 256) / 2 + 2;

    QString style = (m_mapType == Satellite) ? "sate" : (m_mapType == None ? "none" : "pl");
    if (m_trafficEnabled)
        style += "_traf";
    if (m_heatMapEnabled)
        style += "_heat";

    for (int x = centerTileX - rangeX; x <= centerTileX + rangeX; ++x)
    {
        for (int y = centerTileY - rangeY; y <= centerTileY + rangeY; ++y)
        {
            QString key = QString("%1_%2_%3_%4").arg(style).arg(m_zoomLevel).arg(x).arg(y);
            if (!m_tileCache.contains(key))
                m_downloader->downloadTile(x, y, m_zoomLevel, m_ak, style);
        }
    }
}

void MapCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 即使地图没初始化，也先填充一层浅灰色背景
    painter.fillRect(rect(), QColor("#f0f0f0"));

    if (!m_isInitialized)
    {
        painter.setPen(QPen(QColor("#999999"))); // 灰色文字
        painter.drawText(rect(), Qt::AlignCenter, "等待初始化地图...");

        // 同样绘制外边框 (改为浅灰色)
        painter.setPen(QPen(QColor("#dcdcdc"), 2));
        painter.drawRect(rect().adjusted(1, 1, -1, -1));
        return;
    }

    double zoomFactor = qPow(2.0, 18 - m_zoomLevel);
    double mcCenterX = m_centerCoord.x() * 111319.49077777778;
    double mcCenterY = qLn(qTan((m_centerCoord.y() + 90.0) * M_PI / 360.0)) * 6378137.0;

    QString currentStyle = (m_mapType == Satellite) ? "sate" : (m_mapType == None ? "none" : "pl");
    if (m_trafficEnabled)
        currentStyle += "_traf";
    if (m_heatMapEnabled)
        currentStyle += "_heat";

    QString keyPrefix = QString("%1_%2_").arg(currentStyle).arg(m_zoomLevel);

    for (auto it = m_tileCache.begin(); it != m_tileCache.end(); ++it)
    {
        // 只渲染当前 style 和当前 zoom 的瓦片
        if (it.key().startsWith(keyPrefix))
        {
            QStringList parts = it.key().split('_');
            if (parts.size() < 4)
                continue;

            int x = parts[parts.size() - 2].toInt();
            int y = parts[parts.size() - 1].toInt();

            double tileMCX = x * 256.0 * zoomFactor;
            double tileMCY = y * 256.0 * zoomFactor;

            int px = width() / 2 - (mcCenterX - tileMCX) / zoomFactor;
            int py = height() / 2 + (mcCenterY - tileMCY) / zoomFactor;

            painter.drawPixmap(px, py - 256, it.value());
        }
    }

    // 绘制外边框线 (改为浅灰色，增加界面融合度)
    painter.setPen(QPen(QColor("#dcdcdc"), 2)); // 浅灰色 2px
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(1, 1, -1, -1));
}

void MapCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void MapCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning)
    {
        QPoint delta = event->pos() - m_lastMousePos;
        double zoomFactor = qPow(2.0, 18 - m_zoomLevel);

        m_centerCoord.rx() -= (delta.x() * zoomFactor) / 111319.49077777778;
        m_centerCoord.ry() += (delta.y() * zoomFactor) / 111319.49077777778;

        m_lastMousePos = event->pos();
        requestVisibleTiles();
        update();
    }
}

void MapCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPanning = false;
        unsetCursor();
    }
}

void MapCanvas::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        setZoomLevel(m_zoomLevel + 1);
    else
        setZoomLevel(m_zoomLevel - 1);
}
