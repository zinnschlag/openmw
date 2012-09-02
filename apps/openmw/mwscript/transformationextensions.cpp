#include <boost/algorithm/string.hpp>

#include <components/esm_store/store.hpp>

#include <components/compiler/extensions.hpp>

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/runtime.hpp>
#include <components/interpreter/opcodes.hpp>

#include "../mwbase/environment.hpp"

#include "../mwworld/class.hpp"

#include "interpretercontext.hpp"
#include "ref.hpp"
#include "OgreSceneNode.h"


#include "../mwworld/player.hpp"
#include "components\esm\loadcell.hpp"

#include "OgreMath.h"
namespace MWScript
{
    namespace Transformation
    {
        template<class R>
        class OpSetScale : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Float scale = runtime[0].mFloat;
                    runtime.pop();

                    MWBase::Environment::get().getWorld()->scaleObject(ptr,scale);
                }
        };

        template<class R>
        class OpGetScale : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);
                    runtime.push(ptr.getCellRef().scale);
                }
        };

        template<class R>
        class OpSetAngle : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string axis = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();
                    Interpreter::Type_Float angle = runtime[0].mFloat;
                    runtime.pop();

                    float ax = Ogre::Radian(ptr.getRefData().getPosition().rot[0]).valueDegrees();
                    float ay = Ogre::Radian(ptr.getRefData().getPosition().rot[1]).valueDegrees();
                    float az = Ogre::Radian(ptr.getRefData().getPosition().rot[2]).valueDegrees();

                    if (axis == "x")
                    {
                        MWBase::Environment::get().getWorld()->rotateObject(ptr,angle,ay,az);
                    }
                    else if (axis == "y")
                    {
                        MWBase::Environment::get().getWorld()->rotateObject(ptr,ax,angle,az);
                    }
                    else if (axis == "z")
                    {
                        MWBase::Environment::get().getWorld()->rotateObject(ptr,ax,ay,angle);
                    }
                    else
                        throw std::runtime_error ("invalid ration axis: " + axis);
                }
        };

        template<class R>
        class OpGetStartingAngle : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string axis = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    if (axis == "x")
                    {
                        runtime.push(Ogre::Radian(ptr.getRefData().getPosition().rot[0]).valueDegrees());
                    }
                    else if (axis == "y")
                    {
                        runtime.push(Ogre::Radian(ptr.getRefData().getPosition().rot[1]).valueDegrees());
                    }
                    else if (axis == "z")
                    {
                        runtime.push(Ogre::Radian(ptr.getRefData().getPosition().rot[2]).valueDegrees());
                    }
                    else
                        throw std::runtime_error ("invalid ration axis: " + axis);
                }
        };

        template<class R>
        class OpGetAngle : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string axis = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    if (axis=="x")
                    {
                        runtime.push(Ogre::Radian(ptr.getCellRef().pos.rot[0]).valueDegrees());
                    }
                    else if (axis=="y")
                    {
                        runtime.push(Ogre::Radian(ptr.getCellRef().pos.rot[1]).valueDegrees());
                    }
                    else if (axis=="z")
                    {
                        runtime.push(Ogre::Radian(ptr.getCellRef().pos.rot[2]).valueDegrees());
                    }
                    else
                        throw std::runtime_error ("invalid ration axis: " + axis);
                }
        };

        template<class R>
        class OpGetPos : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string axis = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    if(axis == "x")
                    {
                        runtime.push(ptr.getRefData().getPosition().pos[0]);
                    }
                    else if(axis == "y")
                    {
                        runtime.push(ptr.getRefData().getPosition().pos[1]);
                    }
                    else if(axis == "z")
                    {
                        runtime.push(ptr.getRefData().getPosition().pos[2]);
                    }
                }
        };

        template<class R>
        class OpSetPos : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string axis = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();
                    Interpreter::Type_Float pos = runtime[0].mFloat;
                    runtime.pop();

                    float ax = ptr.getRefData().getPosition().pos[0];
                    float ay = ptr.getRefData().getPosition().pos[1];
                    float az = ptr.getRefData().getPosition().pos[2];
                    

                    if(axis == "x")
                    {
                        MWBase::Environment::get().getWorld()->moveObject(ptr,pos,ay,az);
                    }
                    else if(axis == "y")
                    {
                        MWBase::Environment::get().getWorld()->moveObject(ptr,ax,pos,az);
                    }
                    else if(axis == "z")
                    {
                        MWBase::Environment::get().getWorld()->moveObject(ptr,ax,ay,pos);
                    }
                }
        };

        template<class R>
        class OpGetStartingPos : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string axis = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    if(axis == "x")
                    {
                        runtime.push(ptr.getCellRef().pos.pos[0]);
                    }
                    else if(axis == "y")
                    {
                        runtime.push(ptr.getCellRef().pos.pos[1]);
                    }
                    else if(axis == "z")
                    {
                        runtime.push(ptr.getCellRef().pos.pos[2]);
                    }
                }
        };

        template<class R>
        class OpPositionCell : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float zRot = runtime[0].mFloat;
                    runtime.pop();
                    std::string cellID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    MWWorld::CellStore* store = 0;
                    try
                    {
                        store = MWBase::Environment::get().getWorld()->getInterior(cellID);
                    }
                    catch(std::exception &e)
                    {
                        const ESM::Cell* cell = MWBase::Environment::get().getWorld()->getExterior(cellID);
                        if(cell)
                        {
                            int cx,cy;
                            MWBase::Environment::get().getWorld()->positionToIndex(x,y,cx,cy);
                            store = MWBase::Environment::get().getWorld()->getExterior(cx,cy);
                        }
                    }
                    if(store)
                    {
                        MWBase::Environment::get().getWorld()->moveObject(ptr,*store,x,y,z);
                        float ax = Ogre::Radian(ptr.getRefData().getPosition().rot[0]).valueDegrees();
                        float ay = Ogre::Radian(ptr.getRefData().getPosition().rot[1]).valueDegrees();
                        if(ptr.getTypeName() == typeid(ESM::NPC).name())//some morrowind oddity
                        {
                            ax = ax/60.;
                            ay = ay/60.;
                            zRot = zRot/60.;
                        }
                        MWBase::Environment::get().getWorld()->rotateObject(ptr,ax,ay,zRot);
                    }
                    else
                    {
                        throw std::runtime_error ("unknown cell");
                    }
                }
        };

        template<class R>
        class OpPosition : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float zRot = runtime[0].mFloat;
                    runtime.pop();
                    int cx,cy;
                    MWBase::Environment::get().getWorld()->positionToIndex(x,y,cx,cy);
                    MWBase::Environment::get().getWorld()->moveObject(ptr,
                        *MWBase::Environment::get().getWorld()->getExterior(cx,cy),x,y,z);
                    float ax = Ogre::Radian(ptr.getRefData().getPosition().rot[0]).valueDegrees();
                    float ay = Ogre::Radian(ptr.getRefData().getPosition().rot[1]).valueDegrees();
                    if(ptr.getTypeName() == typeid(ESM::NPC).name())//some morrowind oddity
                    {
                        ax = ax/60.;
                        ay = ay/60.;
                        zRot = zRot/60.;
                    }
                    MWBase::Environment::get().getWorld()->rotateObject(ptr,ax,ay,zRot);
                }
        };

        template<class R>
        class OpPlaceItemCell : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    //MWWorld::Ptr ptr = R()(runtime);

                    std::string itemID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();
                    std::string cellID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float zRot = runtime[0].mFloat;
                    runtime.pop();

                    MWWorld::CellStore* store = 0;
                    try
                    {
                        store = MWBase::Environment::get().getWorld()->getInterior(cellID);
                    }
                    catch(std::exception &e)
                    {
                        const ESM::Cell* cell = MWBase::Environment::get().getWorld()->getExterior(cellID);
                        if(cell)
                        {
                            int cx,cy;
                            MWBase::Environment::get().getWorld()->positionToIndex(x,y,cx,cy);
                            store = MWBase::Environment::get().getWorld()->getExterior(cx,cy);
                        }
                    }
                    if(store)
                    {
                        ESM::Position pos;
                        pos.pos[0] = x;
                        pos.pos[1] = y;
                        pos.pos[2] = z;
                        pos.rot[0] = pos.rot[1] = 0;
                        pos.rot[2]  = zRot;
                        MWWorld::Ptr ptr = MWBase::Environment::get().getWorld()->getPtr(itemID,false);
                        MWBase::Environment::get().getWorld()->copyObjectToCell(ptr,*store,pos);
                    }
                    else
                    {
                        throw std::runtime_error ("unknown cell");
                    }
                }
        };

        template<class R>
        class OpPlaceItem : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    //MWWorld::Ptr ptr = R()(runtime);

                    std::string itemID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Float zRot = runtime[0].mFloat;
                    runtime.pop();

                    MWWorld::CellStore* store = 0;
                    int cx,cy;
                    MWBase::Environment::get().getWorld()->positionToIndex(x,y,cx,cy);
                    store = MWBase::Environment::get().getWorld()->getExterior(cx,cy);
                    if(store)
                    {
                        ESM::Position pos;
                        pos.pos[0] = x;
                        pos.pos[1] = y;
                        pos.pos[2] = z;
                        pos.rot[0] = pos.rot[1] = 0;
                        pos.rot[2]  = zRot;
                        MWWorld::Ptr ptr = MWBase::Environment::get().getWorld()->getPtr(itemID,false);
                        MWBase::Environment::get().getWorld()->copyObjectToCell(ptr,*store,pos);
                    }
                    else
                    {
                        throw std::runtime_error ("unknown cell");
                    }
                }
        };

        template<class R>
        class OpPlaceAtPc : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    std::string itemID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Integer count = runtime[0].mInteger;
                    runtime.pop();
                    Interpreter::Type_Float distance = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Integer direction = runtime[0].mInteger;
                    runtime.pop();

                    ESM::Position ipos = MWBase::Environment::get().getWorld()->getPlayer().getPlayer().getRefData().getPosition();
                    Ogre::Vector3 pos(ipos.pos[0],ipos.pos[1],ipos.pos[2]);
                    Ogre::Quaternion rot(Ogre::Radian(ipos.rot[2]), Ogre::Vector3::UNIT_Z);
                    if(direction == 0) pos = pos + distance*rot.yAxis();
                    else if(direction == 1) pos = pos - distance*rot.yAxis();
                    else if(direction == 2) pos = pos - distance*rot.xAxis();
                    else if(direction == 3) pos = pos + distance*rot.xAxis();
                    else throw std::runtime_error ("direction must be 0,1,2 or 3");

                    ipos.pos[0] = pos.x;
                    ipos.pos[1] = pos.y;
                    ipos.pos[2] = pos.z;
                    MWWorld::CellStore* store = MWBase::Environment::get().getWorld()->getPlayer().getPlayer().getCell();                    
                    MWWorld::Ptr ptr = MWBase::Environment::get().getWorld()->getPtr(itemID,false);
                    int icount = ptr.getRefData().getCount();
                    ptr.getRefData().setCount(count);
                    MWBase::Environment::get().getWorld()->copyObjectToCell(ptr,*store,ipos);
                    ptr.getRefData().setCount(icount);
                    //store->ge
                }
        };

        template<class R>
        class OpPlaceAtMe : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr me = R()(runtime);

                    std::string itemID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Integer count = runtime[0].mInteger;
                    runtime.pop();
                    Interpreter::Type_Float distance = runtime[0].mFloat;
                    runtime.pop();
                    Interpreter::Type_Integer direction = runtime[0].mInteger;
                    runtime.pop();

                    ESM::Position ipos = me.getRefData().getPosition();
                    Ogre::Vector3 pos(ipos.pos[0],ipos.pos[1],ipos.pos[2]);
                    Ogre::Quaternion rot(Ogre::Radian(ipos.rot[2]), Ogre::Vector3::UNIT_Z);
                    if(direction == 0) pos = pos + distance*rot.yAxis();
                    else if(direction == 1) pos = pos - distance*rot.yAxis();
                    else if(direction == 2) pos = pos - distance*rot.xAxis();
                    else if(direction == 3) pos = pos + distance*rot.xAxis();
                    else throw std::runtime_error ("direction must be 0,1,2 or 3");

                    ipos.pos[0] = pos.x;
                    ipos.pos[1] = pos.y;
                    ipos.pos[2] = pos.z;
                    MWWorld::CellStore* store = me.getCell();                    
                    MWWorld::Ptr ptr = MWBase::Environment::get().getWorld()->getPtr(itemID,false);
                    int icount = ptr.getRefData().getCount();
                    ptr.getRefData().setCount(count);
                    MWBase::Environment::get().getWorld()->copyObjectToCell(ptr,*store,ipos);
                    ptr.getRefData().setCount(icount);
                    //store->ge
                }
        };

        const int opcodeSetScale = 0x2000164;
        const int opcodeSetScaleExplicit = 0x2000165;
        const int opcodeSetAngle = 0x2000166;
        const int opcodeSetAngleExplicit = 0x2000167;
        const int opcodeGetScale = 0x2000168;
        const int opcodeGetScaleExplicit = 0x2000169;
        const int opcodeGetAngle = 0x200016a;
        const int opcodeGetAngleExplicit = 0x200016b;
        const int opcodeGetPos = 0x200016c;
        const int opcodeGetPosExplicit = 0x200016d;
        const int opcodeSetPos = 0x200016e;
        const int opcodeSetPosExplicit = 0x200016f;
        const int opcodeGetStartingPos = 0x2000170;
        const int opcodeGetStartingPosExplicit = 0x2000171;
        const int opcodePosition = 0x2000172;
        const int opcodePositionExplicit = 0x2000173;
        const int opcodePositionCell = 0x2000174;
        const int opcodePositionCellExplicit = 0x2000175;

        const int opcodePlaceItemCell = 0x2000176;
        const int opcodePlaceItem = 0x2000177;
        const int opcodePlaceAtPc = 0x2000178;  
        const int opcodePlaceAtMe = 0x2000179;
        const int opcodePlaceAtMeExplicit = 0x200017a;

        void registerExtensions (Compiler::Extensions& extensions)
        {
            extensions.registerInstruction("setscale","f",opcodeSetScale,opcodeSetScaleExplicit);
            extensions.registerFunction("getscale",'f',"",opcodeGetScale,opcodeGetScaleExplicit);
            extensions.registerInstruction("setangle","Sf",opcodeSetAngle,opcodeSetAngleExplicit);
            extensions.registerFunction("getangle",'f',"S",opcodeGetAngle,opcodeGetAngleExplicit);
            extensions.registerInstruction("setpos","cf",opcodeSetPos,opcodeSetPosExplicit);
            extensions.registerFunction("getpos",'f',"c",opcodeGetPos,opcodeGetPosExplicit);
            extensions.registerFunction("getstartingpos",'f',"c",opcodeGetStartingPos,opcodeGetStartingPosExplicit);
            extensions.registerInstruction("position","ffff",opcodePosition,opcodePositionExplicit);
            extensions.registerInstruction("positioncell","ffffS",opcodePositionCell,opcodePositionCellExplicit);
            extensions.registerInstruction("placeitemcell","ccffff",opcodePlaceItemCell);
            extensions.registerInstruction("placeitem","cffff",opcodePlaceItem);
            extensions.registerInstruction("placeatpc","clfl",opcodePlaceAtPc);
            extensions.registerInstruction("placeatme","clfl",opcodePlaceAtMe,opcodePlaceAtMeExplicit);
        }

        void installOpcodes (Interpreter::Interpreter& interpreter)
        {
            interpreter.installSegment5(opcodeSetScale,new OpSetScale<ImplicitRef>);
            interpreter.installSegment5(opcodeSetScaleExplicit,new OpSetScale<ExplicitRef>);
            interpreter.installSegment5(opcodeSetAngle,new OpSetAngle<ImplicitRef>);
            interpreter.installSegment5(opcodeSetAngleExplicit,new OpSetAngle<ExplicitRef>);
            interpreter.installSegment5(opcodeGetScale,new OpGetScale<ImplicitRef>);
            interpreter.installSegment5(opcodeGetScaleExplicit,new OpGetScale<ExplicitRef>);
            interpreter.installSegment5(opcodeGetAngle,new OpGetAngle<ImplicitRef>);
            interpreter.installSegment5(opcodeGetAngleExplicit,new OpGetAngle<ExplicitRef>);
            interpreter.installSegment5(opcodeGetPos,new OpGetPos<ImplicitRef>);
            interpreter.installSegment5(opcodeGetPosExplicit,new OpGetPos<ExplicitRef>);
            interpreter.installSegment5(opcodeSetPos,new OpSetPos<ImplicitRef>);
            interpreter.installSegment5(opcodeSetPosExplicit,new OpSetPos<ExplicitRef>);
            interpreter.installSegment5(opcodeGetStartingPos,new OpGetStartingPos<ImplicitRef>);
            interpreter.installSegment5(opcodeGetStartingPosExplicit,new OpGetStartingPos<ExplicitRef>);
            interpreter.installSegment5(opcodePosition,new OpPosition<ImplicitRef>);
            interpreter.installSegment5(opcodePositionExplicit,new OpPosition<ExplicitRef>);
            interpreter.installSegment5(opcodePositionCell,new OpPositionCell<ImplicitRef>);
            interpreter.installSegment5(opcodePositionCellExplicit,new OpPositionCell<ExplicitRef>);
            interpreter.installSegment5(opcodePlaceItemCell,new OpPlaceItemCell<ImplicitRef>);            
            interpreter.installSegment5(opcodePlaceItem,new OpPlaceItem<ImplicitRef>);            
            interpreter.installSegment5(opcodePlaceAtPc,new OpPlaceAtPc<ImplicitRef>);   
            interpreter.installSegment5(opcodePlaceAtMe,new OpPlaceAtPc<ImplicitRef>);   
            interpreter.installSegment5(opcodePlaceAtMeExplicit,new OpPlaceAtPc<ExplicitRef>); 
        }
    }
}
