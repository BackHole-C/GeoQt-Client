#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QWidget>
#include <QMap>
#include "maputils.h"

/**
 * @brief MapCanvas 类是地图渲染的核心画布
 *
 * 负责瓦片地图的绘制、缩放、平移以及覆盖物的渲染。
 */
class MapCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit MapCanvas(QWidget *parent = nullptr);

    /**
     * @brief 初始化地图引擎
     * @param ak 百度地图开放平台访问密钥
     */
    void initMapEngine(const QString &ak);

    /**
     * @brief 获取当前地图中心点坐标
     */
    QPointF centerCoordinate() const { return m_centerCoord; }

private slots:
    void onTileReady(int x, int y, int zoom, const QPixmap &pixmap);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    /**
     * @brief 请求并下载当前屏幕可见的所有瓦片
     */
    void requestVisibleTiles();

    /**
     * @brief 将经纬度坐标转换为本地组件内部的像素坐标
     */
    QPointF coordinateToPixel(const QPointF &coord);

    /**
     * @brief 将组件内的像素点击位置转换为经纬度坐标
     */
    QPointF pixelToCoordinate(const QPoint &pos);

    QString m_ak;
    bool m_isInitialized = false;
    QPointF m_centerCoord = {116.404, 39.915}; 
    int m_zoomLevel = 12;

    class TileDownloader *m_downloader;
    
    // 瓦片存储
    QMap<QString, QPixmap> m_tileCache;
    
    // 交互状态
    bool m_isPanning = false;
    QPoint m_lastMousePos;
};

#endif // MAPCANVAS_H
