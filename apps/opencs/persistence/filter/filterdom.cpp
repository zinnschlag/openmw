#include "filterdom.hpp"

#include <QDebug>
#include <QFile>

Filter *FilterDom::loadFile(QString fileName, Filter *parent)
{
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly))
    {
        QDomDocument document("FilterTree");

        QString parseError;
        int parseErrorRow;
        int parseErrorColumn;

        if (document.setContent(&file, &parseError, &parseErrorRow, &parseErrorColumn))
            return createFilter(document.firstChildElement(), parent);
        else
            qDebug() << "Parse error" << parseError << parseErrorRow << parseErrorColumn;

        file.close();
    }
    else
        qDebug() << "Opening file failed";

    return 0;
}


Filter *FilterDom::createFilter(const QDomElement &element, Filter *parent)
{
    Filter *result = 0;

    QString name = element.tagName();
    if (name == "SetOperation")
        result = createSetOperationFilter(element, parent);
    else if (name == "Match")
        result = createMatchFilter(element, parent);
    else if (name == "Default")
        result = new DefaultFilter(parent);
    else
    {
        qWarning() << "Unknown filter type" << element.tagName();
        return 0;
    }

    QString enabled = element.attribute("active", "true");
    result->setEnabled(enabled == "true" ? true : false);

    QDomElement nameElement = element.firstChildElement("Name");
    result->setName(nameElement.text());


    QDomElement childContainer = element.firstChildElement("ChildItems");
    QDomElement child = childContainer.firstChildElement();
    while(!child.isNull())
    {
        Filter* childFilter = createFilter(child, result);
        result->appendChild(childFilter);

        child = child.nextSiblingElement();
    }

    return result;
}

SetOperationFilter *FilterDom::createSetOperationFilter(const QDomElement &element, Filter* parent)
{
    QString type = element.attribute("type", "Union");

    SetOperationFilter::OperationType matchType = SetOperationFilter::Union;

    if(type == "Union")
        matchType = SetOperationFilter::Union;
    else if(type == "Intersection")
        matchType = SetOperationFilter::Intersection;
    else
        qWarning() << "Unknown type" << type;

    return new SetOperationFilter(matchType, parent);
}

MatchFilter *FilterDom::createMatchFilter(const QDomElement &element, Filter* parent)
{
    QString matchTypeName = element.attribute("type", "Exact");

    MatchFilter::MatchType matchType = MatchFilter::Exact;

    if(matchTypeName == "Exact")
        matchType = MatchFilter::Exact;
    else if(matchTypeName == "Wildcard")
        matchType = MatchFilter::Wildcard;
    else if(matchTypeName == "Regex")
        matchType = MatchFilter::Regex;
    else
        qWarning() << "Unknown match type" << matchTypeName;

    QDomElement keyElement = element.firstChildElement("Key");
    QDomElement matchElement = element.firstChildElement("Value");

    return new MatchFilter(matchType, keyElement.text(), matchElement.text(), parent);
}


