#include <QString>
#include <QtTest>
#include <QNetworkCookie>
#include <QDateTime>


#include <../../../MediaPlayer/src/Network/CookieJar.h>

class CookieJarTest : public QObject
{
    Q_OBJECT
    
public:
    CookieJarTest();
    
private Q_SLOTS:
    void testCreate();
    void testCreate_noCookieFile();
    void test_getterSetter();

    void test_cookiesForUrl_data();
    void test_cookiesForUrl();

    void test_loadSaveCokiesToFile();
    void test_loadCokiesToFile_inConstructor();

    void test_deleteCookie();
    void test_insertCookie();
    void test_setCookiesFromUrl_data();
    void test_setCookiesFromUrl();

    void test_setCookiesFromUrl_GoWeb();

private:

};

CookieJarTest::CookieJarTest()
{
}

void CookieJarTest::testCreate()
{
    CookieJar *cookie = new CookieJar();
    QVERIFY2(cookie!=NULL, "Failure");
}

void CookieJarTest::testCreate_noCookieFile()
{
    //Given
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }

    //when
    CookieJar *cookie = new CookieJar();
    QList<QNetworkCookie> cookieList = cookie->getAllCookies();

    //expected
    QVERIFY(cookieList.isEmpty());
}

void CookieJarTest::test_getterSetter()
{
    //Given
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }
    CookieJar jar;

    //when
    QList<QNetworkCookie> list;
    QNetworkCookie cookie;
    cookie.setName("a");
    list << cookie;
    jar.setAllCookies(list);

    QList<QNetworkCookie> cookieList = jar.getAllCookies();


    //Expexted
    QCOMPARE(cookieList, list);
}

void CookieJarTest::test_cookiesForUrl_data()
{
    QTest::addColumn<QList<QNetworkCookie> >("allCookies");
    QTest::addColumn<QString>("url");
    QTest::addColumn<QList<QNetworkCookie> >("expectedResult");

    QList<QNetworkCookie> allCookies;
    QList<QNetworkCookie> result;

    QTest::newRow("no-cookies") << allCookies << "http://foo.bar/" << result;

    QNetworkCookie cookie;
    cookie.setName("a");
    cookie.setPath("/web");
    cookie.setDomain(".qt-project.org");
    allCookies += cookie;

    QTest::newRow("no-match-1") << allCookies << "http://foo.bar/" << result;
    QTest::newRow("no-match-2") << allCookies << "http://foo.bar/web" << result;
    QTest::newRow("no-match-3") << allCookies << "http://foo.bar/web/wiki" << result;
    QTest::newRow("no-match-4") << allCookies << "http://qt-project.org" << result;
    QTest::newRow("no-match-5") << allCookies << "http://qt-project.org" << result;
    QTest::newRow("no-match-6") << allCookies << "http://qt-project.org/webinar" << result;
    QTest::newRow("no-match-7") << allCookies << "http://qt-project.org/webinar" << result;
    QTest::newRow("no-match-8") << allCookies << "http://qt-project.org./web" << result;
    QTest::newRow("no-match-9") << allCookies << "http://qt-project.org./web" << result;

    result = allCookies;
    QTest::newRow("match-1") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("match-2") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("match-3") << allCookies << "http://qt-project.org/web/content" << result;
    QTest::newRow("match-4") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("match-5") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("match-6") << allCookies << "http://qt-project.org/web/content" << result;

    cookie.setPath("/web/wiki");
    allCookies += cookie;

    // exact same results as before:
    QTest::newRow("one-match-1") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("one-match-2") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("one-match-3") << allCookies << "http://qt-project.org/web/content" << result;
    QTest::newRow("one-match-4") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("one-match-5") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("one-match-6") << allCookies << "http://qt-project.org/web/content" << result;

    result.prepend(cookie);     // longer path, it must match first
    QTest::newRow("two-matches-1") << allCookies << "http://qt-project.org/web/wiki" << result;
    QTest::newRow("two-matches-2") << allCookies << "http://qt-project.org/web/wiki" << result;

    // invert the order;
    allCookies.clear();
    allCookies << result.at(1) << result.at(0);
    QTest::newRow("two-matches-3") << allCookies << "http://qt-project.org/web/wiki" << result;
    QTest::newRow("two-matches-4") << allCookies << "http://qt-project.org/web/wiki" << result;

    // expired cookie
    allCookies.clear();
    cookie.setExpirationDate(QDateTime::fromString("09-Nov-1999", "dd-MMM-yyyy"));
    allCookies += cookie;
    result.clear();
    QTest::newRow("exp-match-1") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("exp-match-2") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("exp-match-3") << allCookies << "http://qt-project.org/web/content" << result;
    QTest::newRow("exp-match-4") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("exp-match-5") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("exp-match-6") << allCookies << "http://qt-project.org/web/content" << result;

    // path matching
    allCookies.clear();
    QNetworkCookie anotherCookie;
    anotherCookie.setName("a");
    anotherCookie.setPath("/web");
    anotherCookie.setDomain(".qt-project.org");
    allCookies += anotherCookie;
    result.clear();
    QTest::newRow("path-unmatch-1") << allCookies << "http://qt-project.org/" << result;
    QTest::newRow("path-unmatch-2") << allCookies << "http://qt-project.org/something/else" << result;
    result += anotherCookie;
    QTest::newRow("path-match-1") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("path-match-2") << allCookies << "http://qt-project.org/web/" << result;
    QTest::newRow("path-match-3") << allCookies << "http://qt-project.org/web/content" << result;

    // secure cookies
    allCookies.clear();
    result.clear();
    QNetworkCookie secureCookie;
    secureCookie.setName("a");
    secureCookie.setPath("/web");
    secureCookie.setDomain(".qt-project.org");
    secureCookie.setSecure(true);
    allCookies += secureCookie;
    QTest::newRow("no-match-secure-1") << allCookies << "http://qt-project.org/web" << result;
    QTest::newRow("no-match-secure-2") << allCookies << "http://qt-project.org/web" << result;
    result += secureCookie;
    QTest::newRow("match-secure-1") << allCookies << "https://qt-project.org/web" << result;
    QTest::newRow("match-secure-2") << allCookies << "https://qt-project.org/web" << result;

    // domain ending in .
    allCookies.clear();
    result.clear();
    QNetworkCookie cookieDot;
    cookieDot.setDomain(".example.com.");
    cookieDot.setName("a");
    allCookies += cookieDot;
    QTest::newRow("no-match-domain-dot") << allCookies << "http://example.com" << result;
    result += cookieDot;
    QTest::newRow("match-domain-dot") << allCookies << "http://example.com." << result;
}

void CookieJarTest::test_cookiesForUrl()
{
    QFETCH(QList<QNetworkCookie>, allCookies);
    QFETCH(QString, url);
    QFETCH(QList<QNetworkCookie>, expectedResult);

    CookieJar jar;
    jar.setAllCookies(allCookies);

    QList<QNetworkCookie> result = jar.cookiesForUrl(url);
    QCOMPARE(result, expectedResult);
}

void CookieJarTest::test_loadSaveCokiesToFile()
{
    //Given
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }
    CookieJar jar;

    QList<QNetworkCookie> list;
    QNetworkCookie cookie;
    cookie.setName("a");
    cookie.setPath("/web");
    cookie.setDomain(".qt-project.org");
    QDateTime expirationDate = QDateTime::fromString("09-01-2018", "dd-MM-yyyy");
    cookie.setExpirationDate(expirationDate);


    list << cookie;
    jar.setAllCookies(list);

    //WHEN
    jar.saveCokiesToFile();
    QList<QNetworkCookie> emptyList;
    jar.setAllCookies(emptyList);
    QList<QNetworkCookie> cookieList = jar.getAllCookies();
    QVERIFY(cookieList.isEmpty());

    jar.loadCookiesFromFile();
    cookieList = jar.getAllCookies();

    //Expexted
    QCOMPARE(cookieList, list);
    QCOMPARE(cookieList.at(0).name(), list.at(0).name());

}


void CookieJarTest::test_loadCokiesToFile_inConstructor()
{
    //Given
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }
    CookieJar jar;

    QList<QNetworkCookie> list;
    QNetworkCookie cookie;
    cookie.setName("a");
    cookie.setPath("/web");
    cookie.setDomain(".qt-project.org");
    QDateTime expirationDate = QDateTime::fromString("09-01-2018", "dd-MM-yyyy");
    cookie.setExpirationDate(expirationDate);


    list << cookie;
    jar.setAllCookies(list);
    jar.saveCokiesToFile();


    //WHEN
    CookieJar jarNew;
    QList<QNetworkCookie> cookieList = jarNew.getAllCookies();

    //Expexted
    QCOMPARE(cookieList, list);
    QCOMPARE(cookieList.at(0).name(), list.at(0).name());

}

void CookieJarTest::test_deleteCookie()
{
    //Given
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }

    CookieJar jar;

    QList<QNetworkCookie> list;
    QNetworkCookie cookie;
    cookie.setName("a");
    cookie.setPath("/web");
    cookie.setDomain(".qt-project.org");
    QDateTime expirationDate = QDateTime::fromString("09-01-2018", "dd-MM-yyyy");
    cookie.setExpirationDate(expirationDate);
    list << cookie;

    cookie.setName("b");
    list << cookie;

    jar.setAllCookies(list);
    QCOMPARE(list.at(0).name(), QString("a").toLocal8Bit());
    QCOMPARE(list.at(1).name(), QString("b").toLocal8Bit());

    //WHEN
    jar.deleteCookie(cookie);
    QList<QNetworkCookie> cookieList = jar.getAllCookies();

    //Expexted
    QCOMPARE(cookieList.size() , 1);
    QCOMPARE(cookieList.at(0).name(), QString("a").toLocal8Bit());

    //WHEN
    CookieJar jarNew;
    cookieList = jarNew.getAllCookies();

    //Expexted
    QCOMPARE(cookieList.size() , 1);
    QCOMPARE(cookieList.at(0).name(), QString("a").toLocal8Bit());
}

void CookieJarTest::test_insertCookie()
{
    //Given
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }

    CookieJar jar;

    QList<QNetworkCookie> list;
    QNetworkCookie cookie;
    cookie.setName("a");
    cookie.setPath("/web");
    cookie.setDomain(".qt-project.org");
    QDateTime expirationDate = QDateTime::fromString("09-01-2018", "dd-MM-yyyy");
    cookie.setExpirationDate(expirationDate);
    list << cookie;

    cookie.setName("b");
    list << cookie;

    jar.setAllCookies(list);
    QCOMPARE(list.at(0).name(), QString("a").toLocal8Bit());
    QCOMPARE(list.at(1).name(), QString("b").toLocal8Bit());

    //WHEN
    cookie.setName("c");

    jar.insertCookie(cookie);
    QList<QNetworkCookie> cookieList = jar.getAllCookies();

    //Expexted
    QCOMPARE(cookieList.size() , 3);
    QCOMPARE(cookieList.at(0).name(), QString("a").toLocal8Bit());
    QCOMPARE(cookieList.at(1).name(), QString("b").toLocal8Bit());
    QCOMPARE(cookieList.at(2).name(), QString("c").toLocal8Bit());

    //WHEN
    CookieJar jarNew;
    cookieList = jarNew.getAllCookies();

    //Expexted
    QCOMPARE(cookieList.size() , 3);
    QCOMPARE(cookieList.at(0).name(), QString("a").toLocal8Bit());
    QCOMPARE(cookieList.at(1).name(), QString("b").toLocal8Bit());
    QCOMPARE(cookieList.at(2).name(), QString("c").toLocal8Bit());
}

void CookieJarTest::test_setCookiesFromUrl_data()
{
    QTest::addColumn<QList<QNetworkCookie> >("preset");
    QTest::addColumn<QNetworkCookie>("newCookie");
    QTest::addColumn<QString>("referenceUrl");
    QTest::addColumn<QList<QNetworkCookie> >("expectedResult");
    QTest::addColumn<bool>("setCookies");

    QList<QNetworkCookie> preset;
    QList<QNetworkCookie> result;
    QNetworkCookie cookie;

    cookie.setName("a");
    cookie.setPath("/");
    cookie.setDomain("www.foo.tld");
    result += cookie;
    cookie.setPath("");
    cookie.setDomain("");
    QTest::newRow("just-add") << preset << cookie << "http://www.foo.tld" << result << true;

    preset = result;
    QTest::newRow("replace-1") << preset << cookie << "http://www.foo.tld" << result << true;

    cookie.setValue("bc");
    result.clear();
    result += cookie;
    QTest::newRow("replace-2") << preset << cookie << "http://www.foo.tld" << result << true;

    preset = result;
    cookie.setName("d");
    result += cookie;
    QTest::newRow("append") << preset << cookie << "http://www.foo.tld" << result << true;

    cookie = preset.at(0);
    result = preset;
    cookie.setPath("/something");
    result += cookie;
    QTest::newRow("diff-path") << preset << cookie << "http://www.foo.tld/something" << result << true;

    preset.clear();
    preset += cookie;
    cookie.setPath("/");
    QTest::newRow("diff-path-order") << preset << cookie << "http://www.foo.tld" << result << true;

    // security test:
    result.clear();
    preset.clear();
    cookie.setDomain("something.completely.different");
    QTest::newRow("security-domain-1") << preset << cookie << "http://www.foo.tld" << result << false;

    cookie.setDomain("www.foo.tld");
    cookie.setPath("/something");
    QTest::newRow("security-path-1") << preset << cookie << "http://www.foo.tld" << result << false;

    // setting the defaults:
    QNetworkCookie finalCookie = cookie;
    finalCookie.setPath("/something/");
    cookie.setPath("");
    cookie.setDomain("");
    result.clear();
    result += finalCookie;
    QTest::newRow("defaults-1") << preset << cookie << "http://www.foo.tld/something/" << result << true;

    finalCookie.setPath("/");
    result.clear();
    result += finalCookie;
    QTest::newRow("defaults-2") << preset << cookie << "http://www.foo.tld" << result << true;

    // security test: do not accept cookie domains like ".com" nor ".com." (see RFC 2109 section 4.3.2)
    result.clear();
    preset.clear();
    cookie.setDomain(".com");
    QTest::newRow("rfc2109-4.3.2-ex3") << preset << cookie << "http://x.foo.com" << result << false;

    result.clear();
    preset.clear();
    cookie.setDomain(".com.");
    QTest::newRow("rfc2109-4.3.2-ex3-2") << preset << cookie << "http://x.foo.com" << result << false;
}

void CookieJarTest::test_setCookiesFromUrl()
{
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }

    QFETCH(QList<QNetworkCookie>, preset);
    QFETCH(QNetworkCookie, newCookie);
    QFETCH(QString, referenceUrl);
    QFETCH(QList<QNetworkCookie>, expectedResult);
    QFETCH(bool, setCookies);

    QList<QNetworkCookie> cookieList;
    cookieList += newCookie;
    CookieJar jar;
    jar.setAllCookies(preset);
    QCOMPARE(jar.setCookiesFromUrl(cookieList, referenceUrl), setCookies);

    QList<QNetworkCookie> result = jar.getAllCookies();
    foreach (QNetworkCookie cookie, expectedResult) {
        QVERIFY2(result.contains(cookie), cookie.toRawForm());
        result.removeAll(cookie);
    }
    QVERIFY2(result.isEmpty(), QTest::toString(result));
}

void CookieJarTest::test_setCookiesFromUrl_GoWeb()
{
    QFile cookies(QDir::homePath()+"/"+CookieJar::COOCKIE_DIR+"/cookies");
    if (cookies.exists()) {
        cookies.remove();
    }

    QList<QNetworkCookie> cookieList;
    QList<QNetworkCookie> expextedResult;

    QUrl url("http://ad.goweb.com/z/52cc775f796086bb8b008351?mw_ch=33&mw_ch_cat=3&ref=sony_pictures1");

    QNetworkCookie newCookie;
    newCookie.setName("s");
    newCookie.setValue("ck7r9184vtponjfvv867k86h21");
    newCookie.setPath("/");
    qDebug().nospace() << "Cookie = " <<newCookie;
    //[ setCookiesFromUrl; (QNetworkCookie("s=ck7r9184vtponjfvv867k86h21; path=/") ,  QNetworkCookie("v=5335025e7960864731008601; expires=Thu, 26-Jun-2014 05:02:22 GMT; path=/") )      QUrl( "http://ad.goweb.com/z/52cc775f796086bb8b008351?mw_ch=33&mw_ch_cat=3&ref=sony_pictures1" )   ]
    cookieList += newCookie;

    newCookie.setDomain(url.host());
    newCookie.setPath(url.path());
    expextedResult +=newCookie;
    qDebug().nospace() << "exp cookie = " << newCookie;

    CookieJar jar;

    //WHEN
    jar.setCookiesFromUrl(cookieList,url);

    //EXPECTED
    QList<QNetworkCookie> result = jar.cookiesForUrl(url);
    QCOMPARE(result, expextedResult);

    qDebug().nospace() << "result = " <<result;
    qDebug().nospace() << "expextedResult = " <<expextedResult;


}

QTEST_APPLESS_MAIN(CookieJarTest)

#include "tst_cookiejartest.moc"
