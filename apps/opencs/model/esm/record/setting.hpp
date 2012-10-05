#ifndef SETTING_HPP
#define SETTING_HPP

#include "../esmdataitem.hpp"

#include <QVariant>

class SettingDataItem : public ESMDataItem
{
    Q_OBJECT

    Q_PROPERTY(QVariant value READ value)

public:
    explicit SettingDataItem(ModelItem *parent);
    ~SettingDataItem();

    virtual void load(ESM::ESMReader &esm);

    QString key();
    QVariant value();

private:
    ESM::GameSetting mSetting;
};

#endif
