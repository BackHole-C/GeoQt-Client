#ifndef MAPUTILS_H
#define MAPUTILS_H

#include <QtMath>
#include <QPointF>

/**
 * @brief MapUtils 命名空间包含地理坐标转换的核心算法
 * 
 * 专门针对百度地图 (BD-09) 的墨卡托投影和瓦片系统进行优化。
 */
namespace MapUtils {
    const double PI = 3.14159265358979323846;
    
    /**
     * @brief TileCoord 结构体表示瓦片的层级和行列索引
     */
    struct TileCoord {
        int x;      // 瓦片 X 轴编号（从西向东）
        int y;      // 瓦片 Y 轴编号（从南向北）
        int zoom;   // 缩放等级
    };

    /**
     * @brief 百度经纬度转百度墨卡托平面坐标 (米)
     * @param lng 经度
     * @param lat 纬度
     * @return 对应的百度 MC 坐标点
     */
    inline QPointF lngLatToMC(double lng, double lat) {
        // 百度经度转 MC 系数
        double x = lng * 111319.49077777778; 
        // 百度纬度转 MC 系数 (基于 WGS84 修正)
        double y = qLn(qTan((lat + 90.0) * PI / 360.0)) * 6378137.0; 
        return QPointF(x, y);
    }

    /**
     * @brief 将百度 MC 坐标转回经纬度
     * @param mcX 百度墨卡托 X
     * @param mcY 百度墨卡托 Y
     * @return QPointF(lng, lat)
     */
    inline QPointF mcToLngLat(double mcX, double mcY) {
        double lng = mcX / 111319.49077777778;
        double lat = qAtan(qExp(mcY / 6378137.0)) * 360.0 / PI - 90.0;
        return QPointF(lng, lat);
    }

    /**
     * @brief 百度经纬度转百度瓦片索引 (BD09 瓦片系统)
     * @param lng 经度
     * @param lat 纬度
     * @param zoom 缩放等级
     * @return TileCoord 瓦片行列和层级
     */
    inline TileCoord lngLatToTile(double lng, double lat, int zoom) {
        QPointF mc = lngLatToMC(lng, lat);
        // 百度瓦片公式: index = floor(MC / (256 * 2^(18-zoom)))
        double zoomFactor = qPow(2.0, 18 - zoom);
        int tileX = qFloor(mc.x() / (256.0 * zoomFactor));
        int tileY = qFloor(mc.y() / (256.0 * zoomFactor));
        
        return { tileX, tileY, zoom };
    }
}

#endif
