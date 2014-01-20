#ifndef USERSETTINGS_HPP
#define USERSETTINGS_HPP

#include <QTextStream>
#include <QStringList>
#include <QString>
#include <QMap>
#include <QSortFilterProxyModel>

#include <boost/filesystem/path.hpp>

#include "settingmodel.hpp"

#ifndef Q_MOC_RUN
#include <components/files/configurationmanager.hpp>
#endif

namespace Files { typedef std::vector<boost::filesystem::path> PathContainer;
                  struct ConfigurationManager;}

class QFile;

namespace CSMSettings {

    class UserSettings: public SettingModel
    {

        Q_OBJECT

        static UserSettings *mUserSettingsInstance;
        QString mUserFilePath;
        Files::ConfigurationManager mCfgMgr;

        QString mReadOnlyMessage;
        QString mReadWriteMessage;

        //setting name, list of setting values
        QMap <QString, QStringList> mDefinitions;

    public:

        /// Singleton implementation
        static UserSettings& instance();

        UserSettings();
        ~UserSettings();

        UserSettings (UserSettings const &);        //not implemented
        void operator= (UserSettings const &);      //not implemented

        /// Writes settings to the last loaded settings file
        bool writeSettings();

        /// Retrieves the settings file at all three levels (global, local and user).
        void loadSettings (const QString &fileName);

        /// Writes settings to the user's config file path
        void saveSettings ();

    private:

        bool loadSettingsFromFile (const QStringList &filepaths);

        void buildSettingModelDefaults();

    signals:

        void signalUpdateEditorSetting (const QString &settingName,
                                        const QString &settingValue);

    };
}
#endif // USERSETTINGS_HPP
