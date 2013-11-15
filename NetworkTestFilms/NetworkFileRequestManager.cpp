#include "NetworkFileRequestManager.h"

NetworkFileRequestManager::NetworkFileRequestManager(QObject *parent) :
    NetworkRequestManager(parent)
{
}

void NetworkFileRequestManager::performFilmsListRequest(int offset)
{
    QUrl url(apiURL_ + "/vod/feed");
    QNetworkRequest request(url);
    if (!userProfile_->token().isEmpty())
        request.setRawHeader("X-Auth-Token", userProfile_->token().toUtf8());
    request.setRawHeader("Accept-Language", /*Settings::sharedInstance()->language().toLocal8Bit()*/"ru");  // TODO put to separate method, which constract HTTP header
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    QUrlQuery q;
    QString offsetStr;
    offsetStr.append(QString("%1").arg(offset));

    q.addQueryItem("offset", offsetStr);
    q.addQueryItem("length", "1");
    q.addQueryItem("sort[date_added]","0");

    QByteArray postData(q.query(QUrl::FullyEncoded).toUtf8());


    QNetworkReply *reply = networkAccessManager_.post(request, postData);
    NetworkRequestManagerConnection *connection = new NetworkRequestManagerConnection(reply);
    QObject::connect(connection, SIGNAL(finished(NetworkRequestManagerConnection *, bool,int)),
                         this, SLOT(processFilmsListResponse(NetworkRequestManagerConnection*,bool,int)));
}

void NetworkFileRequestManager::processFilmsListResponse(NetworkRequestManagerConnection *connection, bool error, int status)
{
    // TODO BUG create our one bin-class
    std::vector<PlaylistModelEntry> entries;

    QByteArray replyData = connection->downloadedData();

    qDebug() << "replyData = connection->downloadedData()" << replyData;

    QJsonParseError errorJsonPars;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(replyData, &errorJsonPars);
    if (jsonDocument.isNull() || !jsonDocument.isObject())
    {
        return;
    }


    QJsonObject object = jsonDocument.object();
    if ((int)object["error"].toDouble() != 0)
    {
        return;
    }


    int totalItems = object["total_items"].toDouble();
    QJsonArray movies = object["items"].toArray();

    foreach (QJsonValue movie, movies)
    {
        if (!movie.isObject())
            continue;

        QJsonObject movieObject = movie.toObject();

        int movieId = (int)movieObject["id"].toDouble();
        QString name = movieObject["name"].toString();
        QString description = movieObject["description"].toString();

        QString url = movieObject["url"].toString();
        QString torrentUrl = movieObject["torrent"].toString();


        QJsonArray genres = movieObject["genres"].toArray();
        QList<int> parsedGenres;
        foreach (QJsonValue genreId, genres)
        {
            int gerStr = (int)genreId.toDouble();
            parsedGenres.append(genreId.toString().toInt());
        }


        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();

        entry.setTitleUtf8(name.toUtf8().data());
        entry.setURLUtf8(url.toUtf8().data());
//        entry.setXmltvid(channelMap["channel_id"].toString().toUtf8().data());
        entry.setTorrentUrlUtf8(torrentUrl.toUtf8().data());
//        entry.setNumber(channelMap["number"].toString().toUtf8().data());

    }

    emit filmsListResponseProcessed(entries);

}
