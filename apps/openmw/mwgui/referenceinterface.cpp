#include "referenceinterface.hpp"

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"

#include "../mwworld/player.hpp"

namespace MWGui
{
    ReferenceInterface::ReferenceInterface()
        : mCurrentPlayerCell(NULL)
    {
    }

    ReferenceInterface::~ReferenceInterface()
    {
    }

    void ReferenceInterface::checkReferenceAvailable()
    {
        if (mPtr.isEmpty())
            return;

        MWWorld::Ptr::CellStore* playerCell = MWBase::Environment::get().getWorld()->getPlayer().getPlayer().getCell();

        // check if player has changed cell, or count of the reference has become 0
        if ((playerCell != mCurrentPlayerCell && mCurrentPlayerCell != NULL)
            || mPtr.getRefData().getCount() == 0)
        {
            mPtr = MWWorld::Ptr();
            onReferenceUnavailable();
        }

        mCurrentPlayerCell = playerCell;
    }
}
