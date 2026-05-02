#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QWidget>
#include <QMap>
#include <QPointF>
#include <QPixmap>

class MapCanvas : public QWidget
{
    Q_OBJECT
public:
    enum MapType
    {
        Normal,    // 普通地图 (MAP_TYPE_NORMAL)
        Satellite, // 卫星图 (MAP_TYPE_SATELLITE)
        None       // 空白地图 (MAP_TYPE_NONE)
    };

    explicit MapCanvas(QWidget *parent = nullptr);

    void initMapEngine(const QString &ak);

    // Getters
    QPointF centerCoordinate() const { return m_centerCoord; }
    int zoomLevel() const { return m_zoomLevel; }
    MapType mapType() const { return m_mapType; }

    // Setters (只保留声明，移动实现到 .cpp 以防重定义且方便以后扩展逻辑)
    void setCenterCoordinate(const QPointF &coord);
    void setZoomLevel(int level);
    void setMapType(MapType type);
    void setTrafficEnabled(bool enabled);
    void setHeatMapEnabled(bool enabled);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void requestVisibleTiles();

    QString m_ak;
    bool m_isInitialized = false;
    QPointF m_centerCoord = {116.404, 39.915};
    int m_zoomLevel = 12;
    MapType m_mapType = Normal;
    bool m_trafficEnabled = false;
    bool m_heatMapEnabled = false;

    class TileDownloader *m_downloader;
    QMap<QString, QPixmap> m_tileCache;

    bool m_isPanning = false;
    QPoint m_lastMousePos;
};

#endif // MAPCANVAS_H
