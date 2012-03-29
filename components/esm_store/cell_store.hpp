#ifndef _GAME_CELL_STORE_H
#define _GAME_CELL_STORE_H

/*
  Cell storage.

  Used to load, look up and store all references in a single cell.

  Depends on esm/loadcell.hpp (loading from ESM) and esm_store.hpp
  (looking up references.) Neither of these modules depend on us.
 */

#include "store.hpp"
#include "components/esm/records.hpp"

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace ESMS
{
  using namespace ESM;

  /// A reference to one object (of any type) in a cell.
  ///
  /// Constructing this with a CellRef instance in the constructor means that
  /// in practice (where D is RefData) the possibly mutable data is copied
  /// across to mData. If later adding data (such as position) to CellRef
  /// this would have to be manually copied across.
  template <typename X, typename D>
  struct LiveCellRef
  {
    LiveCellRef(const CellRef& cref, const X* b = NULL) : base(b), ref(cref),
                                                          mData(ref) {}


    LiveCellRef(const X* b = NULL) : base(b), mData(ref) {}

    // The object that this instance is based on.
    const X* base;

    /* Information about this instance, such as 3D location and
       rotation and individual type-dependent data.
    */
    CellRef ref;

    /// runtime-data
    D mData;
  };

  /// A list of cell references
  template <typename X, typename D>
  struct CellRefList
  {
    typedef LiveCellRef<X, D> LiveRef;
    typedef std::list<LiveRef> List;
    List list;

    // Search for the given reference in the given reclist from
    // ESMStore. Insert the reference into the list if a match is
    // found. If not, throw an exception.
    template <typename Y>
    void find(CellRef &ref, const Y& recList)
    {
      const X* obj = recList.find(ref.refID);
      if(obj == NULL)
        throw std::runtime_error("Error resolving cell reference " + ref.refID);

      list.push_back(LiveRef(ref, obj));
    }

    LiveRef *find (const std::string& name)
    {
        for (typename std::list<LiveRef>::iterator iter (list.begin()); iter!=list.end(); ++iter)
        {
            if (iter->ref.refID==name)
                return &*iter;
        }

        return 0;
    }
  };

  /// A storage struct for one single cell reference.
  template <typename D>
  class CellStore
  {
  public:

    enum State
    {
        State_Unloaded, State_Preloaded, State_Loaded
    };

    CellStore (const ESM::Cell *cell_) : cell (cell_), mState (State_Unloaded)
    {
        mWaterLevel = cell->water;
    }

    const ESM::Cell *cell;
    State mState;
    std::vector<std::string> mIds;

    float mWaterLevel;

    // Lists for each individual object type
    CellRefList<Activator, D>         activators;
    CellRefList<Potion, D>            potions;
    CellRefList<Apparatus, D>         appas;
    CellRefList<Armor, D>             armors;
    CellRefList<Book, D>              books;
    CellRefList<Clothing, D>          clothes;
    CellRefList<Container, D>         containers;
    CellRefList<Creature, D>          creatures;
    CellRefList<Door, D>              doors;
    CellRefList<Ingredient, D>        ingreds;
    CellRefList<CreatureLevList, D>   creatureLists;
    CellRefList<ItemLevList, D>       itemLists;
    CellRefList<ESM::Light, D>        lights;
    CellRefList<Tool, D>              lockpicks;
    CellRefList<Miscellaneous, D>              miscItems;
    CellRefList<NPC, D>               npcs;
    CellRefList<Probe, D>             probes;
    CellRefList<Repair, D>            repairs;
    CellRefList<Static, D>            statics;
    CellRefList<Weapon, D>            weapons;

    void load (const ESMStore &store, ESMReader &esm)
    {
        if (mState!=State_Loaded)
        {
            if (mState==State_Preloaded)
                mIds.clear();

            std::cout << "loading cell " << cell->getDescription() << std::endl;

            loadRefs (store, esm);

            mState = State_Loaded;
        }
    }

    void preload (const ESMStore &store, ESMReader &esm)
    {
        if (mState==State_Unloaded)
        {
            listRefs (store, esm);

            mState = State_Preloaded;
        }
    }

    /// Call functor (ref) for each reference. functor must return a bool. Returning
    /// false will abort the iteration.
    /// \return Iteration completed?
    template<class Functor>
    bool forEach (Functor& functor)
    {
        return
            forEachImp (functor, activators) &&
            forEachImp (functor, potions) &&
            forEachImp (functor, appas) &&
            forEachImp (functor, armors) &&
            forEachImp (functor, books) &&
            forEachImp (functor, clothes) &&
            forEachImp (functor, containers) &&
            forEachImp (functor, creatures) &&
            forEachImp (functor, doors) &&
            forEachImp (functor, ingreds) &&
            forEachImp (functor, creatureLists) &&
            forEachImp (functor, itemLists) &&
            forEachImp (functor, lights) &&
            forEachImp (functor, lockpicks) &&
            forEachImp (functor, miscItems) &&
            forEachImp (functor, npcs) &&
            forEachImp (functor, probes) &&
            forEachImp (functor, repairs) &&
            forEachImp (functor, statics) &&
            forEachImp (functor, weapons);
    }

  private:

    template<class Functor, class List>
    bool forEachImp (Functor& functor, List& list)
    {
        for (typename List::List::iterator iter (list.list.begin()); iter!=list.list.end();
            ++iter)
            if (!functor (iter->ref, iter->mData))
                return false;

        return true;
    }

    /// Run through references and store IDs
    void listRefs(const ESMStore &store, ESMReader &esm)
    {
        assert (cell);

        if (cell->context.filename.empty())
            return; // this is a dynamically generated cell -> skipping.

        // Reopen the ESM reader and seek to the right position.
        cell->restore (esm);

        CellRef ref;

        // Get each reference in turn
        while (cell->getNextRef (esm, ref))
        {
            std::string lowerCase;

            std::transform (ref.refID.begin(), ref.refID.end(), std::back_inserter (lowerCase),
                (int(*)(int)) std::tolower);

            mIds.push_back (lowerCase);
        }

        std::sort (mIds.begin(), mIds.end());
    }

    void loadRefs(const ESMStore &store, ESMReader &esm)
    {
      assert (cell);

        if (cell->context.filename.empty())
            return; // this is a dynamically generated cell -> skipping.

      // Reopen the ESM reader and seek to the right position.
      cell->restore(esm);

      CellRef ref;

      // Get each reference in turn
      while(cell->getNextRef(esm, ref))
        {
            std::string lowerCase;

            std::transform (ref.refID.begin(), ref.refID.end(), std::back_inserter (lowerCase),
                (int(*)(int)) std::tolower);

            int rec = store.find(ref.refID);

            ref.refID = lowerCase;

          /* We can optimize this further by storing the pointer to the
             record itself in store.all, so that we don't need to look it
             up again here. However, never optimize. There are infinite
             opportunities to do that later.
           */
          switch(rec)
            {
            case REC_ACTI: activators.find(ref, store.activators); break;
            case REC_ALCH: potions.find(ref, store.potions); break;
            case REC_APPA: appas.find(ref, store.appas); break;
            case REC_ARMO: armors.find(ref, store.armors); break;
            case REC_BOOK: books.find(ref, store.books); break;
            case REC_CLOT: clothes.find(ref, store.clothes); break;
            case REC_CONT: containers.find(ref, store.containers); break;
            case REC_CREA: creatures.find(ref, store.creatures); break;
            case REC_DOOR: doors.find(ref, store.doors); break;
            case REC_INGR: ingreds.find(ref, store.ingreds); break;
            case REC_LEVC: creatureLists.find(ref, store.creatureLists); break;
            case REC_LEVI: itemLists.find(ref, store.itemLists); break;
            case REC_LIGH: lights.find(ref, store.lights); break;
            case REC_LOCK: lockpicks.find(ref, store.lockpicks); break;
            case REC_MISC: miscItems.find(ref, store.miscItems); break;
            case REC_NPC_: npcs.find(ref, store.npcs); break;
            case REC_PROB: probes.find(ref, store.probes); break;
            case REC_REPA: repairs.find(ref, store.repairs); break;
            case REC_STAT: statics.find(ref, store.statics); break;
            case REC_WEAP: weapons.find(ref, store.weapons); break;

            case 0: std::cout << "Cell reference " + ref.refID + " not found!\n"; break;
            default:
              std::cout << "WARNING: Ignoring reference '" << ref.refID << "' of unhandled type\n";
            }
        }
    }

  };
}

#endif
