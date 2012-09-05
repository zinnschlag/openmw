#ifndef FILTERFILE_HPP
#define FILTERFILE_HPP

#include "../modelitem.hpp"

class FilterFile : public ModelItem
{
    Q_OBJECT

public:
    explicit FilterFile(ModelItem *parent = 0) : ModelItem(parent) {}
    ~FilterFile() {}
};

#endif
