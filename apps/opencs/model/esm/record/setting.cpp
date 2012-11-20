#include "setting.hpp"

#include <QDebug>

SettingDataItem::SettingDataItem(ModelItem *parent)
    : ESMDataItem(parent)
{}

SettingDataItem::~SettingDataItem()
{}

void SettingDataItem::load(ESM::ESMReader &esm)
{
    //FIXME WTF
    mSetting.mId = mId.toStdString();

    mSetting.load(esm);
}

QString SettingDataItem::key()
{
    return QString::fromStdString(mSetting.mId);
}

QVariant SettingDataItem::value()
{
    switch(mSetting.mType) {
    case ESM::VT_None:
        return QVariant(QVariant::Invalid);
    case ESM::VT_String:
        return QVariant(QString::fromStdString(mSetting.mStr));
    case ESM::VT_Int:
        return QVariant(mSetting.mI);
    case ESM::VT_Float:
        return QVariant(mSetting.mF);
    default:
        qDebug() << "Unexpected data type" << mSetting.mType;
        return QVariant();
    };
}
