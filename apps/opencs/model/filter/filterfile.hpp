#ifndef FILTERFILE_HPP
#define FILTERFILE_HPP

#include "../modelitem.hpp"
#include "filter.hpp"

class FilterFile : public ModelItem
{
    Q_OBJECT

public:
    explicit FilterFile(ModelItem *parent = 0) : ModelItem(parent) {}
    ~FilterFile() {}

    QString fileName() {return mFileName;}
    void setFileName(QString name) {mFileName = name;}

private:
    QString mFileName;
};

#endif
