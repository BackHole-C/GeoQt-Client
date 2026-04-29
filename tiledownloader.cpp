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

void TileDownloader::downloadTile(int x, int y, int zoom, const QString &ak)
{
    QString key = QString("%1_%2_%3").arg(zoom).arg(x).arg(y);
    if (m_cache.contains(key)) {
        emit tileDownloaded(x, y, zoom, m_cache[key]);
        return;
    }

    // 纠正后的百度地图瓦片请求参数
    // qt=tile: 关键参数，表示请求瓦片数据
    // styles=pl: 街道图层
    // udt: 版本时间戳
    QString urlStr = QString("https://maponline0.bdimg.com/tile/?qt=tile&x=%1&y=%2&z=%3&styles=pl&scaler=1&udt=20230519")
                         .arg(x)
                         .arg(y)
                         .arg(zoom);

    qDebug() << "Fetching Corrected Tile:" << urlStr;

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36");

    m_manager->get(request);
}

void TileDownloader::clearCache()
{
    m_cache.clear();
}

void TileDownloader::onDownloadFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QUrl url = reply->url();
        QUrlQuery query(url);
        int x = query.queryItemValue("x").toInt();
        int y = query.queryItemValue("y").toInt();
        int z = query.queryItemValue("z").toInt();

        QByteArray data = reply->readAll();
        QPixmap pixmap;
        if (pixmap.loadFromData(data))
        {
            QString key = QString("%1_%2_%3").arg(z).arg(x).arg(y);
            m_cache[key] = pixmap;
            emit tileDownloaded(x, y, z, pixmap);
        }
    }
    else
    {
        emit downloadError(reply->errorString());
    }
    reply->deleteLater();
}
