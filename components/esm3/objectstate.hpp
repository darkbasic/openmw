#ifndef OPENMW_ESM_OBJECTSTATE_H
#define OPENMW_ESM_OBJECTSTATE_H

#include <string>
#include <vector>

#include "animationstate.hpp"
#include "cellref.hpp"
#include "components/esm/luascripts.hpp"
#include "locals.hpp"

namespace ESM
{
    class ESMReader;
    class ESMWriter;
    struct ContainerState;
    struct CreatureLevListState;
    struct CreatureState;
    struct DoorState;
    struct NpcState;

    // format 0, saved games only

    ///< \brief Save state for objects, that do not use custom data
    struct ObjectState
    {
        CellRef mRef;

        unsigned char mHasLocals;
        Locals mLocals;
        LuaScripts mLuaScripts;
        unsigned char mEnabled;
        int mCount;
        Position mPosition;
        unsigned int mFlags;

        // Is there any class-specific state following the ObjectState
        bool mHasCustomState;

        unsigned int mVersion;

        AnimationState mAnimationState;

        ObjectState()
            : mHasLocals(0)
            , mEnabled(0)
            , mCount(0)
            , mFlags(0)
            , mHasCustomState(true)
            , mVersion(0)
        {
        }

        /// @note Does not load the CellRef ID, it should already be loaded before calling this method
        virtual void load(ESMReader& esm);

        virtual void save(ESMWriter& esm, bool inInventory = false) const;

        /// Initialize to default state
        virtual void blank();

        virtual ~ObjectState();

        virtual const NpcState& asNpcState() const;
        virtual NpcState& asNpcState();

        virtual const CreatureState& asCreatureState() const;
        virtual CreatureState& asCreatureState();

        virtual const ContainerState& asContainerState() const;
        virtual ContainerState& asContainerState();

        virtual const DoorState& asDoorState() const;
        virtual DoorState& asDoorState();

        virtual const CreatureLevListState& asCreatureLevListState() const;
        virtual CreatureLevListState& asCreatureLevListState();
    };
}

#endif
