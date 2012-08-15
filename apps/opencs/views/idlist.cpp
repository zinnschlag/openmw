#include "idlist.hpp"
#include "ui_idlist.h"

#include "idlistitemdelegate.hpp"

#include <QDebug>
#include <QtGui>






QList<QStandardItem *> list;

IdList::IdList(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::IdList)
{
    ui->setupUi(this);

    mFilterProxyModel = new FilterProxyModel(this);

    IdlistItemDelegate *itemDelegate = new IdlistItemDelegate();
    ui->tableView->setItemDelegate(itemDelegate);

    ui->tableView->setModel(mFilterProxyModel);
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->horizontalHeader()->setMovable(true);
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    //ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);

    connect(mFilterProxyModel, SIGNAL(layoutChanged()), ui->tableView, SLOT(resizecolumnsToContents()));
}

IdList::~IdList()
{
    delete ui;
}

void IdList::setModel(QAbstractItemModel *model)
{
    mFilterProxyModel->setSourceModel(model);
}

void IdList::setFilterModel(FilterEditModel *editModel)
{
    mFilterProxyModel->setEditModel(editModel);
}

//FIXME Copy Paste
void IdList::loadColumnConfig()
{
    QFile file(":/columns.xml");
    if (file.open(QIODevice::ReadOnly))
    {
        QDomDocument document("ColumnConfig");

        QString parseError;
        int parseErrorRow;
        int parseErrorColumn;

        if (document.setContent(&file, &parseError, &parseErrorRow, &parseErrorColumn))
        {
            QDomElement columnElement = document.firstChildElement().firstChildElement();
            while (!columnElement.isNull())
            {
                readColumnConfig(columnElement);
                columnElement = columnElement.nextSiblingElement();
            }

            QStringList headers;
            for(int i=0;i<mFilterProxyModel->columnCount(); i++) {
                QVariant header = mFilterProxyModel->headerData(i, Qt::Horizontal);
                headers.append(header.toString());
            }


            for(int u=0; u<mColumnConfigs.size(); u++) {
                QString key = mColumnConfigs.at(u)->key;

                int realPos = headers.indexOf(key);
                if(realPos>u) {
                    ui->tableView->horizontalHeader()->moveSection(realPos, u);
                    headers.move(realPos, u);
                    continue;
                }
            }

            for(int u=0; u<mColumnConfigs.size(); u++) {
                int width = mColumnConfigs.at(u)->width;

                int logical = ui->tableView->horizontalHeader()->logicalIndex(u);
                ui->tableView->horizontalHeader()->resizeSection(logical, width);
            }

        }
        else
        {
            qDebug() << "Parse error" << parseError << parseErrorRow << parseErrorColumn;
        }

        file.close();
    }
    else
    {
        qDebug() << "Opening file failed";
    }
}

void IdList::readColumnConfig(const QDomElement &element)
{
    QString name = element.tagName();
    if (name == "Column")
    {
        QDomElement keyNode = element.firstChildElement("Key");
        QDomElement widthNode = element.firstChildElement("Width");

        mColumnConfigs.append(new ColumnConfig(keyNode.text(), widthNode.text().toInt()));
    } else {
        qWarning() << "Unknown Dom Element" << name;
    }
}
