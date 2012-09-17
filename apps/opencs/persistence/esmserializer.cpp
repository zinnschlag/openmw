#include "esmserializer.hpp"

#include <QDebug>

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

#include "../model/esm/esmfile.hpp"
#include "../model/esm/esmdataitem.hpp"

#include "../model/esm/record/activator.hpp"
#include "../model/esm/record/potion.hpp"
#include "../model/esm/record/script.hpp"
#include "../model/esm/record/setting.hpp"

void EsmSerializer::load(EsmFile *fileItem)
{
    qDebug() << "Trying to open esm:" << fileItem->filename();

    std::string stdStrFileName = fileItem->filename().toStdString();

    ESM::ESMReader reader;
    reader.setEncoding("default");
    reader.open(stdStrFileName);

    while (reader.hasMoreRecs())
    {
        reader.getContext();

        ESM::NAME recordType = reader.getRecName();
        reader.getRecHeader();

        std::string id = reader.getHNOString("NAME");
        QString recordId = QString::fromStdString(id);

        ESMDataItem *child = NULL;

        switch (recordType.val)
        {
        case ESM::REC_ACTI:
            child = new ActivatorDataItem(fileItem);
            break;
        case ESM::REC_ALCH:
            child = new PotionDataItem(fileItem);
            break;
        case ESM::REC_SCPT:
            child = new ScriptDataItem(fileItem);
            break;
        case ESM::REC_GMST:
            child = new SettingDataItem(fileItem);
            break;
        default:
            child = new ESMDataItem(fileItem);
            break;
        }

        child->setRecordType(QString::fromStdString(recordType.toString()));
        child->setId(recordId);

        child->load(reader);

        fileItem->appendChild(child);
    }
}
