#ifndef ESMSERIALIZER_HPP
#define ESMSERIALIZER_HPP

#include <QObject>

#include "../model/esm/esmfile.hpp"

class EsmSerializer : public QObject
{
    Q_OBJECT

public:
    EsmSerializer(QObject *parent = 0) : QObject(parent) {}
    ~EsmSerializer(){}

    void load(EsmFile* fileItem);
private:
};

#endif
