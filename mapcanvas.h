#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QWidget>

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

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    // 后续将在此添加地图缩放等级、中心点经纬度等变量
};

#endif // MAPCANVAS_H
