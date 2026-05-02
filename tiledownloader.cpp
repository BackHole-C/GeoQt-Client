#include "tiledownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

TileDownloader::TileDownloader(QObject *parent)
    : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &TileDownloader::onDownloadFinished);
}

void TileDownloader::downloadTile(int x, int y, int zoom, const QString &ak, const QString &style)
{
    static int serverIdx = 0;
    int s = serverIdx++ % 4;
    
    QString urlStr;
    
    if (style.contains("sate")) {
        // 使用 starpic 接口获取卫星影像
        urlStr = QString("https://maponline%1.bdimg.com/starpic/?qt=satepc&u=x=%2;y=%3;z=%4;v=009;type=sate&fm=46")
                     .arg(s).arg(x).arg(y).arg(zoom);
    } else if (style.contains("none")) {
        urlStr = QString("https://maponline%1.bdimg.com/tile/?qt=vtile&x=%2&y=%3&z=%4&styles=sl&scaler=1&udt=20240321")
                     .arg(s).arg(x).arg(y).arg(zoom);
    } else {
        // 标准普通图 (vtile)
        urlStr = QString("https://maponline%1.bdimg.com/tile/?qt=vtile&x=%2&y=%3&z=%4&styles=pl&scaler=1&udt=20240321")
                     .arg(s).arg(x).arg(y).arg(zoom);
    }

    if (style.contains("traf")) {
         if (urlStr.contains("styles=")) {
             urlStr.replace("styles=pl", "styles=t");
             urlStr.replace("styles=sl", "styles=t");
         }
    }

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setRawHeader("Referer", "https://map.baidu.com/");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36");
    
    QNetworkReply *reply = m_manager->get(request);
    reply->setProperty("tileX", x);
    reply->setProperty("tileY", y);
    reply->setProperty("tileZ", zoom);
    reply->setProperty("tileStyle", style); // 关键：保存完整的 style
}

void TileDownloader::onDownloadFinished(QNetworkReply *reply)
{
    int x = reply->property("tileX").toInt();
    int y = reply->property("tileY").toInt();
    int z = reply->property("tileZ").toInt();
    QString style = reply->property("tileStyle").toString();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QPixmap pix;
        if (pix.loadFromData(data)) {
            // 返回真实的 style 字符串，而不再是 "dynamic"
            emit tileDownloaded(x, y, z, style, pix);
        }
    }
    reply->deleteLater();
}

void TileDownloader::clearCache() { m_cache.clear(); }
