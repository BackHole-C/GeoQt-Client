#include "mapcanvas.h"
#include "tiledownloader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtMath>

MapCanvas::MapCanvas(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color: #f0f0f0;");

    m_downloader = new TileDownloader(this);
    connect(m_downloader, &TileDownloader::tileDownloaded, this, &MapCanvas::onTileReady);
}

/**
 * @brief MapCanvas::paintEvent 核心渲染函数
 * 
 * 1. 计算当前中心点在百度 MC 坐标下的位置。
 * 2. 确定缩放因子（1像素对应的 MC 单位）。
 * 3. 遍历并绘制屏幕可见范围内的瓦片网格。
 * 4. 绘制 HUD 叠加信息层。
 */
void MapCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!m_isInitialized)
    {
        painter.setPen(Qt::gray);
        painter.drawText(rect(), Qt::AlignCenter, "请在左侧面板输入百度地图 AK 以初始化地图引擎");
        return;
    }

    // 1. 获取中心点的百度 MC 坐标
    double mcX = m_centerCoord.x() * 111319.49077777778;
    double mcY = qLn(qTan((m_centerCoord.y() + 90.0) * M_PI / 360.0)) * 6378137.0;

    // 2. 计算当前缩放等级下，1像素对应多少 MC 单位
    // 百度地图公式: 1像素 = 2^(18-zoom) MC单位
    double zoomFactor = qPow(2.0, 18 - m_zoomLevel);
    
    int halfW = width() / 2;
    int halfH = height() / 2;

    // 3. 计算可见瓦片范围
    int centerTileX = qFloor(mcX / (256.0 * zoomFactor));
    int centerTileY = qFloor(mcY / (256.0 * zoomFactor));

    // 屏幕内大约可以容纳的瓦片数量
    int rangeX = (width() / 256) / 2 + 1;
    int rangeY = (height() / 256) / 2 + 1;

    for (int x = centerTileX - rangeX; x <= centerTileX + rangeX; ++x) {
        for (int y = centerTileY - rangeY; y <= centerTileY + rangeY; ++y) {
            QString key = QString("%1_%2_%3").arg(m_zoomLevel).arg(x).arg(y);
            
            // 计算瓦片左上角的 MC 坐标
            double tileMcX = x * 256.0 * zoomFactor;
            double tileMcY = (y + 1) * 256.0 * zoomFactor; // 注意 Y 轴方向

            // 转换为相对于屏幕中心的像素偏移
            double offX = (tileMcX - mcX) / zoomFactor + halfW;
            double offY = halfH - (tileMcY - mcY) / zoomFactor;

            if (m_tileCache.contains(key)) {
                painter.drawPixmap(offX, offY, m_tileCache[key]);
            } else {
                painter.setPen(QColor(200, 200, 200));
                painter.setBrush(QColor(230, 230, 230));
                painter.drawRect(offX, offY, 256, 256);
                painter.setPen(Qt::gray);
                painter.drawText(QRectF(offX, offY, 256, 256), Qt::AlignCenter, QString("%1,%2").arg(x).arg(y));
            }
        }
    }

    // 绘制 HUD 信息
    painter.setPen(Qt::black);
    painter.setBrush(QColor(255, 255, 255, 180));
    QRect infoRect(10, 10, 280, 80);
    painter.drawRoundedRect(infoRect, 5, 5);
    QString info = QString("中心经纬度: %1, %2\n当前缩放等级: %3\n瓦片范围: %4, %5")
                       .arg(m_centerCoord.x(), 0, 'f', 6)
                       .arg(m_centerCoord.y(), 0, 'f', 6)
                       .arg(m_zoomLevel)
                       .arg(centerTileX).arg(centerTileY);
    painter.drawText(infoRect.adjusted(10, 5, -10, -5), Qt::AlignLeft | Qt::AlignTop, info);
}

void MapCanvas::initMapEngine(const QString &ak)
{
    m_ak = ak;
    m_isInitialized = true;
    requestVisibleTiles();
    update();
}

void MapCanvas::requestVisibleTiles()
{
    if (!m_isInitialized) return;

    double mcX = m_centerCoord.x() * 111319.49077777778;
    double mcY = qLn(qTan((m_centerCoord.y() + 90.0) * M_PI / 360.0)) * 6378137.0;
    double zoomFactor = qPow(2.0, 18 - m_zoomLevel);

    int centerTileX = qFloor(mcX / (256.0 * zoomFactor));
    int centerTileY = qFloor(mcY / (256.0 * zoomFactor));

    int rangeX = (width() / 256) / 2 + 1;
    int rangeY = (height() / 256) / 2 + 1;

    for (int x = centerTileX - rangeX; x <= centerTileX + rangeX; ++x) {
        for (int y = centerTileY - rangeY; y <= centerTileY + rangeY; ++y) {
            QString key = QString("%1_%2_%3").arg(m_zoomLevel).arg(x).arg(y);
            if (!m_tileCache.contains(key)) {
                m_downloader->downloadTile(x, y, m_zoomLevel, m_ak);
            }
        }
    }
}

void MapCanvas::onTileReady(int x, int y, int zoom, const QPixmap &pixmap)
{
    if (zoom != m_zoomLevel) return;
    QString key = QString("%1_%2_%3").arg(zoom).arg(x).arg(y);
    m_tileCache[key] = pixmap;
    update();
}

void MapCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void MapCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        // 百度墨卡托坐标下的平移
        double zoomFactor = qPow(2.0, 18 - m_zoomLevel);
        
        // 像素偏移转 MC 偏移
        double mcDeltaX = delta.x() * zoomFactor;
        double mcDeltaY = delta.y() * zoomFactor;

        // 更新中心点的经纬度 (近似计算)
        double currentMcX = m_centerCoord.x() * 111319.49077777778;
        double currentMcY = qLn(qTan((m_centerCoord.y() + 90.0) * M_PI / 360.0)) * 6378137.0;

        double newMcX = currentMcX - mcDeltaX;
        double newMcY = currentMcY + mcDeltaY;

        m_centerCoord.setX(newMcX / 111319.49077777778);
        m_centerCoord.setY(atan(exp(newMcY / 6378137.0)) * 360.0 / M_PI - 90.0);

        requestVisibleTiles();
        update();
    }
}

void MapCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
}

void MapCanvas::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        if (m_zoomLevel < 19) m_zoomLevel++;
    } else {
        if (m_zoomLevel > 3) m_zoomLevel--;
    }
    
    // 缩放后清除旧等级的无效缓存请求
    requestVisibleTiles();
    update();
}
