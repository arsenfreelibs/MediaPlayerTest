#include <QString>
#include <QtTest>
#include <QUrlQuery>
#include <../../../MediaPlayer/src/Protocol/NetworkRequestManager.h>

class ComplexPreviewPlaylistTest : public QObject
{
    Q_OBJECT
    
public:
    ComplexPreviewPlaylistTest();
    
private Q_SLOTS:
    void testCase1();


private:
    NetworkRequestManager networkRequestManager_;
//    PreviewPlaylistController previewPlaylistController_;

private:
    void performAuthorizeRequest();
};

ComplexPreviewPlaylistTest::ComplexPreviewPlaylistTest()
{

}

void ComplexPreviewPlaylistTest::testCase1()
{
    performAuthorizeRequest();
    QVERIFY2(true, "Failure");
}

void ComplexPreviewPlaylistTest::performAuthorizeRequest()
{
    QNetworkAccessManager networkAccessManager_;

    QUrl url("https://tvapi.goweb.com/1.0/users/authorize");
    QNetworkRequest request(url);
    request.setRawHeader("Accept-Language", "uk,ru;q=0.8,en;q=0.6");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    QUrlQuery tmpQuery;
    tmpQuery.addQueryItem("email", QUrl::toPercentEncoding("3816459@i.ua"));

    tmpQuery.addQueryItem("password", QUrl::toPercentEncoding("<fqrfkmcrfz 57,"));
    tmpQuery.addQueryItem("remember", QString::number((int)0).toUtf8());
    tmpQuery.addQueryItem("application_version", QUrl::toPercentEncoding(QCoreApplication::applicationVersion()));
    tmpQuery.addQueryItem("os_type", "Windows");
    tmpQuery.addQueryItem("os_version", QString::number((qulonglong)QSysInfo::windowsVersion()).toUtf8());

    //url.setQuery(tmpQuery);

    QByteArray data = tmpQuery.query().toLocal8Bit();


    QNetworkReply *reply = networkAccessManager_.post(request,data);
    while(!reply->isFinished());

}

QTEST_APPLESS_MAIN(ComplexPreviewPlaylistTest)

#include "tst_complexpreviewplaylisttest.moc"

