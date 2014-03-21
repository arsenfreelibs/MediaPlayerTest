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
    void test_setCookiesFromUrl();

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

void CookieJarTest::test_setCookiesFromUrl()
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
    QList<QNetworkCookie> urlCookieList;
    cookie.setName("f");
    cookie.setPath("/web/wiki");
    cookie.setDomain(".qt-project.org");
    cookie.setExpirationDate(expirationDate);
    urlCookieList << cookie;

    bool result = jar.setCookiesFromUrl(urlCookieList,QUrl("http://qt-project.org/web/wiki"));
    QList<QNetworkCookie> cookieList = jar.getAllCookies();

    //Expexted
    QVERIFY2(result, "Failure setCookiesFromUrl");
    QCOMPARE(cookieList.size() , 3);
    QCOMPARE(cookieList.at(0).name(), QString("a").toLocal8Bit());
    QCOMPARE(cookieList.at(1).name(), QString("b").toLocal8Bit());
    QCOMPARE(cookieList.at(2).domain(), QString(".freelibs.com"));

//    //WHEN
//    CookieJar jarNew;
//    cookieList = jarNew.getAllCookies();

//    //Expexted
//    QCOMPARE(cookieList.size() , 2);
//    QCOMPARE(cookieList.at(0).name(), QString("a").toLocal8Bit());
//    QCOMPARE(cookieList.at(1).name(), QString("b").toLocal8Bit());
//    QCOMPARE(cookieList.at(1).domain(), QString(".freelibs.com"));
}

QTEST_APPLESS_MAIN(CookieJarTest)

#include "tst_cookiejartest.moc"
