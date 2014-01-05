
#include "aiextensions.hpp"

#include <components/compiler/extensions.hpp>
#include <components/compiler/opcodes.hpp>

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/runtime.hpp>
#include <components/interpreter/opcodes.hpp>

#include "../mwworld/class.hpp"

#include "../mwmechanics/creaturestats.hpp"
#include "../mwmechanics/aiactivate.hpp"
#include "../mwmechanics/aiescort.hpp"
#include "../mwmechanics/aifollow.hpp"
#include "../mwmechanics/aitravel.hpp"
#include "../mwmechanics/aiwander.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

#include "interpretercontext.hpp"
#include "ref.hpp"

#include <iostream>

#include "../mwbase/mechanicsmanager.hpp"

namespace MWScript
{
    namespace Ai
    {
        template<class R>
        class OpAiActivate : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string objectID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiActivate activatePackage(objectID);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(activatePackage);
                    std::cout << "AiActivate" << std::endl;
                }
        };

        template<class R>
        class OpAiTravel : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiTravel travelPackage(x, y, z);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(travelPackage);

                    std::cout << "AiTravel: " << x << ", " << y << ", " << z << std::endl;
                }
        };

        template<class R>
        class OpAiEscort : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Float duration = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiEscort escortPackage(actorID, duration, x, y, z);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(escortPackage);

                    std::cout << "AiEscort: " << x << ", " << y << ", " << z << ", " << duration
                        << std::endl;
                }
        };

        template<class R>
        class OpAiEscortCell : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    std::string cellID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Float duration = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiEscort escortPackage(actorID, cellID, duration, x, y, z);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(escortPackage);

                    std::cout << "AiEscort: " << x << ", " << y << ", " << z << ", " << duration
                        << std::endl;
                }
        };

        template<class R>
        class OpGetAiPackageDone : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer value = MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().isPackageDone();

                    runtime.push (value);
                }
        };

        template<class R>
        class OpAiWander : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer range = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Integer duration = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Integer time = runtime[0].mFloat;
                    runtime.pop();

                    std::vector<int> idleList;
                    bool repeat = false;

                    for(int i=1; i < 10 && arg0; ++i)
                    {
                        if(!repeat)
                            repeat = true;
                        Interpreter::Type_Integer idleValue = runtime[0].mInteger;
                        idleList.push_back(idleValue);
                        runtime.pop();
                        --arg0;
                    }

                    if(arg0)
                    {
                        repeat = runtime[0].mInteger != 0;
                        runtime.pop();
                        --arg0;
                    }

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiWander wanderPackage(range, duration, time, idleList, repeat);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(wanderPackage);
                }
        };

        template<class R>
        class OpGetAiSetting : public Interpreter::Opcode0
        {
            int mIndex;
            public:
                OpGetAiSetting(int index) : mIndex(index) {}

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    runtime.push(MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSetting (
                                     (MWMechanics::CreatureStats::AiSetting)mIndex).getModified());
                }
        };
        template<class R>
        class OpModAiSetting : public Interpreter::Opcode0
        {
            int mIndex;
            public:
                OpModAiSetting(int index) : mIndex(index) {}

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);
                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWMechanics::CreatureStats::AiSetting setting
                            = MWMechanics::CreatureStats::AiSetting(mIndex);

                    MWWorld::Class::get (ptr).getCreatureStats (ptr).setAiSetting (setting,
                        MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSetting (setting).getBase() + value);
                }
        };
        template<class R>
        class OpSetAiSetting : public Interpreter::Opcode0
        {
            int mIndex;
            public:
                OpSetAiSetting(int index) : mIndex(index) {}

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);
                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWMechanics::CreatureStats::AiSetting setting = (MWMechanics::CreatureStats::AiSetting)mIndex;

                    MWMechanics::Stat<int> stat = ptr.getClass().getCreatureStats(ptr).getAiSetting(setting);
                    stat.setModified(value, 0);
                    ptr.getClass().getCreatureStats(ptr).setAiSetting(setting, stat);
                }
        };

        template<class R>
        class OpAiFollow : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Float duration = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiFollow followPackage(actorID, duration, x, y ,z);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(followPackage);

                    std::cout << "AiFollow: " << actorID << ", " << x << ", " << y << ", " << z << ", " << duration
                        << std::endl;
                }
        };

        template<class R>
        class OpAiFollowCell : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    std::string cellID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Float duration = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float x = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float y = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float z = runtime[0].mFloat;
                    runtime.pop();

                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWMechanics::AiFollow followPackage(actorID, cellID, duration, x, y ,z);
                    MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().stack(followPackage);
                    std::cout << "AiFollow: " << actorID << ", " << x << ", " << y << ", " << z << ", " << duration
                        << std::endl;
                }
        };

        template<class R>
        class OpGetCurrentAIPackage : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer value = MWWorld::Class::get (ptr).getCreatureStats (ptr).getAiSequence().getTypeId ();

                    runtime.push (value);
                }
        };

        template<class R>
        class OpGetDetected : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Integer value = false; // TODO replace with implementation

                    std::cout << "AiGetDetected: " << actorID << ", " << value << std::endl;

                    runtime.push (value);
                }
        };

        template<class R>
        class OpGetLineOfSight : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {

                    MWWorld::Ptr source = R()(runtime);

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    MWWorld::Ptr dest = MWBase::Environment::get().getWorld()->getPtr(actorID,true);
                    bool value = false;
                    if(dest != MWWorld::Ptr() )
                    {
                        value = MWBase::Environment::get().getWorld()->getLOS(source,dest);
                    }
                    runtime.push (value);
                }
        };

        template<class R>
        class OpToggleAI : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWBase::Environment::get().getMechanicsManager()->toggleAI();   
                }
        };

        void installOpcodes (Interpreter::Interpreter& interpreter)
        {
            interpreter.installSegment3 (Compiler::Ai::opcodeAIActivate, new OpAiActivate<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAIActivateExplicit, new OpAiActivate<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiTravel, new OpAiTravel<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiTravelExplicit, new OpAiTravel<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiEscort, new OpAiEscort<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiEscortExplicit, new OpAiEscort<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiEscortCell, new OpAiEscortCell<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiEscortCellExplicit, new OpAiEscortCell<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiWander, new OpAiWander<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiWanderExplicit, new OpAiWander<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiFollow, new OpAiFollow<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiFollowExplicit, new OpAiFollow<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiFollowCell, new OpAiFollowCell<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeAiFollowCellExplicit, new OpAiFollowCell<ExplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeGetAiPackageDone, new OpGetAiPackageDone<ImplicitRef>);

            interpreter.installSegment5 (Compiler::Ai::opcodeGetAiPackageDoneExplicit,
                new OpGetAiPackageDone<ExplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeGetCurrentAiPackage, new OpGetCurrentAIPackage<ImplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeGetCurrentAiPackageExplicit, new OpGetCurrentAIPackage<ExplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeGetDetected, new OpGetDetected<ImplicitRef>);
            interpreter.installSegment3 (Compiler::Ai::opcodeGetDetectedExplicit, new OpGetDetected<ExplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeGetLineOfSight, new OpGetLineOfSight<ImplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeGetLineOfSightExplicit, new OpGetLineOfSight<ExplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeToggleAI, new OpToggleAI<ImplicitRef>);
            interpreter.installSegment5 (Compiler::Ai::opcodeToggleAIExplicit, new OpToggleAI<ExplicitRef>);

            interpreter.installSegment5 (Compiler::Ai::opcodeSetHello, new OpSetAiSetting<ImplicitRef>(0));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetHelloExplicit, new OpSetAiSetting<ExplicitRef>(0));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetFight, new OpSetAiSetting<ImplicitRef>(1));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetFightExplicit, new OpSetAiSetting<ExplicitRef>(1));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetFlee, new OpSetAiSetting<ImplicitRef>(2));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetFleeExplicit, new OpSetAiSetting<ExplicitRef>(2));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetAlarm, new OpSetAiSetting<ImplicitRef>(3));
            interpreter.installSegment5 (Compiler::Ai::opcodeSetAlarmExplicit, new OpSetAiSetting<ExplicitRef>(3));

            interpreter.installSegment5 (Compiler::Ai::opcodeModHello, new OpModAiSetting<ImplicitRef>(0));
            interpreter.installSegment5 (Compiler::Ai::opcodeModHelloExplicit, new OpModAiSetting<ExplicitRef>(0));
            interpreter.installSegment5 (Compiler::Ai::opcodeModFight, new OpModAiSetting<ImplicitRef>(1));
            interpreter.installSegment5 (Compiler::Ai::opcodeModFightExplicit, new OpModAiSetting<ExplicitRef>(1));
            interpreter.installSegment5 (Compiler::Ai::opcodeModFlee, new OpModAiSetting<ImplicitRef>(2));
            interpreter.installSegment5 (Compiler::Ai::opcodeModFleeExplicit, new OpModAiSetting<ExplicitRef>(2));
            interpreter.installSegment5 (Compiler::Ai::opcodeModAlarm, new OpModAiSetting<ImplicitRef>(3));
            interpreter.installSegment5 (Compiler::Ai::opcodeModAlarmExplicit, new OpModAiSetting<ExplicitRef>(3));

            interpreter.installSegment5 (Compiler::Ai::opcodeGetHello, new OpGetAiSetting<ImplicitRef>(0));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetHelloExplicit, new OpGetAiSetting<ExplicitRef>(0));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetFight, new OpGetAiSetting<ImplicitRef>(1));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetFightExplicit, new OpGetAiSetting<ExplicitRef>(1));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetFlee, new OpGetAiSetting<ImplicitRef>(2));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetFleeExplicit, new OpGetAiSetting<ExplicitRef>(2));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetAlarm, new OpGetAiSetting<ImplicitRef>(3));
            interpreter.installSegment5 (Compiler::Ai::opcodeGetAlarmExplicit, new OpGetAiSetting<ExplicitRef>(3));
        }
    }
}
