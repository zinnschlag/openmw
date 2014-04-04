#include <QDebug>

#include "setting.hpp"
#include "../../view/settings/support.hpp"

CSMSettings::Setting::Setting()
{
    buildDefaultSetting();
}

CSMSettings::Setting::Setting(SettingType typ, const QString &settingName,
                             const QString &pageName)
{
    buildDefaultSetting();

    int vType = static_cast <int> (typ);

    if ((vType % 2) == 0)
        setProperty (Property_IsMultiValue,
                                QVariant(true).toString());
    else
        vType--;

    setProperty (Property_ViewType, QVariant (vType / 2).toString());
    setProperty (Property_Page, pageName);
    setProperty (Property_Name, settingName);
}

void CSMSettings::Setting::dumpSettingValues()
{
    for (int i = 0; i < mLayout.size(); i++)
        qDebug() << sPropertyNames[i] << ':' << mLayout[i];
}

void CSMSettings::Setting::buildDefaultSetting()
{
    int arrLen = sizeof(sPropertyDefaults) / sizeof (*sPropertyDefaults);

    for (int i = 0; i < arrLen; i++)
        mLayout.append(QStringList() << sPropertyDefaults[i]);
}

void CSMSettings::Setting::addProxy (Setting *setting,
                                     QMap <QString, QStringList> &proxyMap)
{
    // proxyMap is keyed to master proxy declared values and contains
    // corresponding proxy values for each declared value for the passed setting

    bool doNew = true;

    foreach (const ProxySettingPair *settingPairItem, mProxyLists)
    {
        StringPair *proxyName = settingPairItem->first;

        if (proxyName->first == setting->page() &&
            proxyName->second == setting->name())
        {
            doNew = false;
            //otherwise, take the existing proxy list and add the new data
            foreach (const QString &key, proxyMap.keys())
            {
                bool success = false;

                ProxyValueList *valueList = settingPairItem->second;

                //iterate the existing keys and replace existing list, if found
                for (int j = 0; j < valueList->size(); j++)
                {
                    const StringListPair *item = valueList->at(j);

                    success = (item->first == key);

                    if (success)
                    {
                        StringListPair *newItem =
                                new StringListPair (key, proxyMap.value (key));

                        valueList->replace(j, newItem);
                        break;
                    }
                }

                //if keyis not found, add to the list
                if (!success)
                    valueList->append
                               (new StringListPair (key, proxyMap.value (key)));
            }
            break;
        }
    }

    if (doNew)
    {
        //if the setting is not found, push a new proxy setting
        ProxyValueList *proxyValueList = new ProxyValueList();

        StringPair *proxyNames  =
                new StringPair(setting->page(), setting->name());

        foreach (const QString &key, proxyMap.keys())
            proxyValueList->append
                                (new StringListPair(key, proxyMap.value(key)));

        ProxySettingPair *proxyItem  =
                        new ProxySettingPair(proxyNames, proxyValueList);

        mProxyLists.append (proxyItem);
    }
}

void CSMSettings::Setting::setDeclaredValues (QStringList list)
{
    mDeclarations = list;
}

const QStringList &CSMSettings::Setting::declaredValues() const
{
    return mDeclarations;
}

void CSMSettings::Setting::setDefinedValues (QStringList list)
{
    mDefinitions = list;
}

const QStringList &CSMSettings::Setting::definedValues() const
{
    return mDefinitions;
}

QVariant CSMSettings::Setting::property (SettingProperty prop) const
{
    if (prop >= mLayout.size())
        return QVariant();

    QStringList propValues = mLayout.at(prop);

    if (propValues.isEmpty())
        return QVariant();

    if (propValues.size() == 1)
        return propValues.at(0);

    return propValues;
}

void CSMSettings::Setting::setDefaultValues (const QStringList &values)
{
    setProperty (Property_DefaultValues, values);
}

QStringList CSMSettings::Setting::defaultValues() const
{
    return property (Property_DefaultValues).toStringList();
}

void CSMSettings::Setting::setDelimiter (const QString &value)
{
    setProperty (Property_Delimiter, value);
}

QString CSMSettings::Setting::delimiter() const
{
    return property (Property_Delimiter).toString();
}

void CSMSettings::Setting::setIsMultiLine (bool state)
{
    setProperty (Property_IsMultiLine, state);
}

bool CSMSettings::Setting::isMultiLine() const
{
    return property (Property_IsMultiLine).toBool();
}

void CSMSettings::Setting::setIsMultiValue (bool state)
{
    setProperty (Property_IsMultiValue, state);
}

bool CSMSettings::Setting::isMultiValue() const
{
    return property (Property_IsMultiValue).toBool();
}

const CSMSettings::ProxyLists &CSMSettings::Setting::proxyLists() const
{
    return mProxyLists;
}

void CSMSettings::Setting::setSerializable (bool state)
{
    setProperty (Property_Serializable, state);
}

bool CSMSettings::Setting::serializable() const
{
    return property (Property_Serializable).toBool();
}

void CSMSettings::Setting::setName (const QString &value)
{
    setProperty (Property_Name, value);
}

QString CSMSettings::Setting::name() const
{
    return property (Property_Name).toString();
}

void CSMSettings::Setting::setPage (const QString &value)
{
    setProperty (Property_Page, value);
}

QString CSMSettings::Setting::page() const
{
    return property (Property_Page).toString();
}

void CSMSettings::Setting::setViewType (int vType)
{
    setProperty (Property_ViewType, vType);
}

CSVSettings::ViewType CSMSettings::Setting::viewType() const
{
    return static_cast <CSVSettings::ViewType>
                                        (property(Property_ViewType).toInt());
}

void CSMSettings::Setting::setViewColumn (int value)
{
    setProperty (Property_ViewColumn, value);
}

int CSMSettings::Setting::viewColumn() const
{
    return property (Property_ViewColumn).toInt();
}

void CSMSettings::Setting::setViewRow (int value)
{
    setProperty (Property_ViewRow, value);
}

int CSMSettings::Setting::viewRow() const
{
    return property (Property_ViewRow).toInt();
}

void CSMSettings::Setting::setWidgetWidth (int value)
{
    setProperty (Property_WidgetWidth, value);
}

int CSMSettings::Setting::widgetWidth() const
{
    return property (Property_WidgetWidth).toInt();
}
void CSMSettings::Setting::setProperty (SettingProperty prop, bool value)
{
    setProperty (prop, QVariant (value).toStringList());
}

void CSMSettings::Setting::setProperty (SettingProperty prop, int value)
{
    setProperty (prop, QVariant (value).toStringList());
}

void CSMSettings::Setting::setProperty (SettingProperty prop,
                                                        const QVariant &value)
{
    setProperty (prop, value.toStringList());
}

void CSMSettings::Setting::setProperty (SettingProperty prop,
                                                        const QString &value)
{
    setProperty (prop, QStringList() << value);
}

void CSMSettings::Setting::setProperty (SettingProperty prop,
                                                    const QStringList &value)
{
    if (prop < mLayout.size())
        mLayout.replace (prop, value);
}

QDataStream &operator <<(QDataStream &stream, const CSMSettings::Setting& setting)
{
    stream<<setting.mLayout;
    stream<<setting.mDefinitions;
    stream<<setting.mDeclarations;
    return stream;
}

QDataStream &operator >>(QDataStream& stream, CSMSettings::Setting& setting)
{
    stream>>setting.mLayout;
    stream>>setting.mDefinitions;
    stream>>setting.mDeclarations;
    return stream;
}