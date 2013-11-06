#include "NetworkFileRequestManager.h"

NetworkFileRequestManager::NetworkFileRequestManager(QObject *parent) :
    NetworkRequestManager(parent)
{
}

void NetworkFileRequestManager::performFilmsListRequest()
{
    QUrl url(apiURL_ + "/vod/feed");
    QNetworkRequest request(url);
    if (!userProfile_->token().isEmpty())
        request.setRawHeader("X-Auth-Token", userProfile_->token().toUtf8());
    request.setRawHeader("Accept-Language", /*Settings::sharedInstance()->language().toLocal8Bit()*/"ru");  // TODO put to separate method, which constract HTTP header

    QUrlQuery q;
    q.addQueryItem("offset", 0);

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



        entries.push_back(PlaylistModelEntry());
        PlaylistModelEntry &entry = entries.back();

        entry.setTitleUtf8(name);
        entry.setURLUtf8(channelMap["url"].toString().toUtf8().data());
        entry.setXmltvid(channelMap["channel_id"].toString().toUtf8().data());
        entry.setTorrentUrlUtf8(channelMap["torrent"].toString().toUtf8().data());
        entry.setNumber(channelMap["number"].toString().toUtf8().data());

    }

    emit filmsListResponseProcessed(entries);

}
