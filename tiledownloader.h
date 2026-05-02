#ifndef TILEDOWNLOADER_H
#define TILEDOWNLOADER_H

#include <QObject>
#include <QPixmap>
#include <QMap>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QNetworkReply;
QT_END_NAMESPACE

/**
 * @brief TileDownloader 类负责从百度地图 API 异步下载地图瓦片
 *
 * 包含简单的内存缓存机制，避免同一会话内重复下载相同瓦片。
 */
class TileDownloader : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit TileDownloader(QObject *parent = nullptr);

    /**
     * @brief 下载指定坐标和缩放等级的瓦片
     * @param x 瓦片 X 坐标
     * @param y 瓦片 Y 坐标
     * @param zoom 缩放等级
     * @param ak 百度地图 AK
     * @param styles 地图样式类型 (默认 "pl" 为普通街道图)
     */
    void downloadTile(int x, int y, int zoom, const QString &ak, const QString &styles = "pl");

    /**
     * @brief 清除内存缓存
     */
    void clearCache();

signals:
    /**
     * @brief 瓦片下载完成信号
     * @param x 瓦片 X 坐标
     * @param y 瓦片 Y 坐标
     * @param zoom 缩放等级
     * @param pixmap 下载后的图像数据
     */
    void tileDownloaded(int x, int y, int zoom, const QString &styles, const QPixmap &pixmap);

    /**
     * @brief 请求失败信号
     */
    void downloadError(const QString &error);

private slots:
    /**
     * @brief 网络响应处理槽函数
     */
    void onDownloadFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager; // 网络管理器
    QMap<QString, QPixmap> m_cache;   // 内存缓存 (Key: "z_x_y")
};

#endif // TILEDOWNLOADER_H
