# The application version
VERSION = 0.0.0.0

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"


TEMPLATE = subdirs

SUBDIRS += \
    PlaylistModelTest \
    TVGidSqlModel \
    DBConnection \
    TVFileController \
    UpdateController \
    AutomaticVersionGenerator \
    UpdateComplexTest \
    GoWebInstaller \
    Advertisement \
    SettingTest \
    DropDownModel \
    PlayerPreSetting \
    PreviewPlaylistControllerTest \
    CookieJar
