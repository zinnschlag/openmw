
#include "scenesubview.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "../../model/doc/document.hpp"

#include "../filter/filterbox.hpp"

#include "../render/pagedworldspacewidget.hpp"
#include "../render/unpagedworldspacewidget.hpp"

#include "tablebottombox.hpp"
#include "creator.hpp"
#include "scenetoolbar.hpp"
#include "scenetoolmode.hpp"

CSVWorld::SceneSubView::SceneSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document)
: SubView (id)
{
    QVBoxLayout *layout = new QVBoxLayout;

    layout->setContentsMargins (QMargins (0, 0, 0, 0));

    layout->addWidget (mBottom =
        new TableBottomBox (NullCreatorFactory(), document.getData(), document.getUndoStack(), id,
        this), 0);

    QHBoxLayout *layout2 = new QHBoxLayout;

    layout2->setContentsMargins (QMargins (0, 0, 0, 0));

    SceneToolbar *toolbar = new SceneToolbar (48, this);

    if (id.getId()=="sys::default")
        mScene = new CSVRender::PagedWorldspaceWidget (this);
    else
        mScene = new CSVRender::UnpagedWorldspaceWidget (id.getId(), document, this);

    SceneToolMode *navigationTool = mScene->makeNavigationSelector (toolbar);
    toolbar->addTool (navigationTool);

    SceneToolMode *lightingTool = mScene->makeLightingSelector (toolbar);
    toolbar->addTool (lightingTool);

    layout2->addWidget (toolbar, 0);

    layout2->addWidget (mScene, 1);

    layout->insertLayout (0, layout2, 1);

    CSVFilter::FilterBox *filterBox = new CSVFilter::FilterBox (document.getData(), this);

    layout->insertWidget (0, filterBox);

    QWidget *widget = new QWidget;

    widget->setLayout (layout);

    setWidget (widget);

    mScene->selectDefaultNavigationMode();

    connect (mScene, SIGNAL (closeRequest()), this, SLOT (closeRequest()));

    connect(filterBox, SIGNAL(recordDropped(std::vector<CSMWorld::UniversalId>&, Qt::DropAction)),
            this, SLOT(createFilterRequest(std::vector<CSMWorld::UniversalId>&, Qt::DropAction)));

      connect(this, SIGNAL(createFilterRequest(std::vector<std::pair<std::string, std::vector<std::string> > >&, Qt::DropAction)),
            filterBox, SIGNAL(createFilterRequest(std::vector<std::pair<std::string, std::vector<std::string> > >&, Qt::DropAction)));
}

void CSVWorld::SceneSubView::setEditLock (bool locked)
{


}

void CSVWorld::SceneSubView::updateEditorSetting(const QString &settingName, const QString &settingValue)
{


}

void CSVWorld::SceneSubView::setStatusBar (bool show)
{
    mBottom->setStatusBar (show);
}

void CSVWorld::SceneSubView::closeRequest()
{
    deleteLater();
}

void CSVWorld::SceneSubView::createFilterRequest (std::vector< CSMWorld::UniversalId>& types, Qt::DropAction action)
{
    std::vector<std::pair<std::string, std::vector<std::string> > > filterSource;

    for (std::vector<CSMWorld::UniversalId>::iterator it = types.begin(); it != types.end(); ++it)
    {
        if (it->getType() == CSMWorld::UniversalId::Type_Cell ||
            it->getType() == CSMWorld::UniversalId::Type_Region)
        {
            std::vector<std::string> id;
            id.push_back("Id");

            std::pair<std::string, std::vector<std::string> > pair(                         //splited long line
            std::make_pair(it->getId(), id));
            filterSource.push_back(pair);
            break;
        }

    }
    emit createFilterRequest(filterSource, action);
}