
#include "aiextensions.hpp"

#include <components/compiler/extensions.hpp>

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/runtime.hpp>
#include <components/interpreter/opcodes.hpp>

#include "../mwworld/class.hpp"

#include "../mwmechanics/creaturestats.hpp"
#include "../mwmechanics/npcstats.hpp"

#include "interpretercontext.hpp"
#include "ref.hpp"

#include <iostream>

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

					MWWorld::Class::get (ptr).getNpcStats (ptr).setAiActivate (objectID);
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

                    MWWorld::Class::get (ptr).getNpcStats (ptr).setAiTravel (x, y, z);
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

                    MWWorld::Class::get (ptr).getNpcStats (ptr).setAiEscort (actorID, duration, x, y, z);
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

                    MWWorld::Class::get (ptr).getNpcStats (ptr).setAiEscortCell (actorID, cellID, duration, x, y, z);
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

                    Interpreter::Type_Integer value = MWWorld::Class::get (ptr).getNpcStats (ptr).getGetAiPackageDone ();

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

                    Interpreter::Type_Float range = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float duration = runtime[0].mFloat;
                    runtime.pop();

                    Interpreter::Type_Float time = runtime[0].mFloat;
                    runtime.pop();

                    // discard additional idle arguments for now
                    // discard additional arguments (reset), because we have no idea what they mean.
                    for (unsigned int i=0; i<arg0; ++i) runtime.pop();

                    MWWorld::Class::get (ptr).getNpcStats (ptr).setAiWander (range, duration, time);
                    std::cout << "AiWanter" << std::endl;
                }
        };

        template<class R>
        class OpSetHello : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWWorld::Class::get (ptr).getCreatureStats (ptr).setAiSetting (0, value);
                }
        };

        template<class R>
        class OpSetFight : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWWorld::Class::get (ptr).getCreatureStats (ptr).setAiSetting (1, value);
                }
        };

        template<class R>
        class OpSetFlee : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWWorld::Class::get (ptr).getCreatureStats (ptr).setAiSetting (2, value);
                }
        };

        template<class R>
        class OpSetAlarm : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer value = runtime[0].mInteger;
                    runtime.pop();

                    MWWorld::Class::get (ptr).getCreatureStats (ptr).setAiSetting (3, value);
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

                    MWWorld::Class::get (ptr).getNpcStats (ptr).setAiFollow (actorID, duration, x, y, z);
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

                    MWWorld::Class::get (ptr).getNpcStats (ptr).setAiFollowCell (actorID, cellID, duration, x, y, z);
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

                    Interpreter::Type_Integer value = MWWorld::Class::get (ptr).getNpcStats (ptr).getGetCurrentAIPackage ();

                    runtime.push (value);
                }
        };

        template<class R>
        class OpGetDetected : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    std::string actorID = runtime.getStringLiteral (runtime[0].mInteger);
                    runtime.pop();

                    Interpreter::Type_Integer value = MWWorld::Class::get (ptr).getNpcStats(ptr).getAiGetDetected (actorID);

                    std::cout << "AiGetDetected: " << actorID << ", " << value << std::endl;

                    runtime.push (value);
                }
        };


        const int opcodeAiTravel = 0x20000;
        const int opcodeAiTravelExplicit = 0x20001;
        const int opcodeAiEscort = 0x20002;
        const int opcodeAiEscortExplicit = 0x20003;
        const int opcodeGetAiPackageDone = 0x200007c;
        const int opcodeGetAiPackageDoneExplicit = 0x200007d;
        const int opcodeGetCurrentAiPackage = 0x20001b1;
        const int opcodeGetCurrentAiPackageExplicit = 0x20001b2;
        const int opcodeGetDetected = 0x20001b3;
        const int opcodeGetDetectedExplicit = 0x20001b4;
        const int opcodeAiWander = 0x20010;
        const int opcodeAiWanderExplicit = 0x20011;
        const int opcodeAIActivate = 0x20018;
        const int opcodeAIActivateExplicit = 0x20019;
        const int opcodeAiEscortCell = 0x2001a;
        const int opcodeAiEscortCellExplicit = 0x2001b;
        const int opcodeAiFollow = 0x2001c;
        const int opcodeAiFollowExplicit = 0x2001d;
        const int opcodeAiFollowCell = 0x2001e;
        const int opcodeAiFollowCellExplicit = 0x2001f;
        const int opcodeSetHello = 0x200015e;
        const int opcodeSetHelloExplicit = 0x200015d;
        const int opcodeSetFight = 0x200015e;
        const int opcodeSetFightExplicit = 0x200015f;
        const int opcodeSetFlee = 0x2000160;
        const int opcodeSetFleeExplicit = 0x2000161;
        const int opcodeSetAlarm = 0x2000162;
        const int opcodeSetAlarmExplicit = 0x2000163;

        void registerExtensions (Compiler::Extensions& extensions)
        {
            extensions.registerInstruction ("aiactivate", "c/l", opcodeAIActivate,
                opcodeAIActivateExplicit);
            extensions.registerInstruction ("aitravel", "fff/l", opcodeAiTravel,
                opcodeAiTravelExplicit);
            extensions.registerInstruction ("aiescort", "cffff/l", opcodeAiEscort,
                opcodeAiEscortExplicit);
            extensions.registerInstruction ("aiescortcell", "ccffff/l", opcodeAiEscortCell,
                opcodeAiEscortCellExplicit);
            extensions.registerInstruction ("aiwander", "fff/llllllllll", opcodeAiWander,
                opcodeAiWanderExplicit);
            extensions.registerInstruction ("aifollow", "cffff/l", opcodeAiFollow,
                opcodeAiFollowExplicit);
            extensions.registerInstruction ("aifollowcell", "ccffff/l", opcodeAiFollowCell,
                opcodeAiFollowCellExplicit);
            extensions.registerFunction ("getaipackagedone", 'l', "", opcodeGetAiPackageDone,
                opcodeGetAiPackageDoneExplicit);
            extensions.registerFunction ("getcurrentaipackage", 'l', "", opcodeGetCurrentAiPackage,
                opcodeGetAiPackageDoneExplicit);
            extensions.registerFunction ("getdetected", 'l', "c", opcodeGetDetected,
                opcodeGetDetectedExplicit);
            extensions.registerInstruction ("sethello", "l", opcodeSetHello, opcodeSetHelloExplicit);
            extensions.registerInstruction ("setfight", "l", opcodeSetFight, opcodeSetFightExplicit);
            extensions.registerInstruction ("setflee", "l", opcodeSetFlee, opcodeSetFleeExplicit);
            extensions.registerInstruction ("setalarm", "l", opcodeSetAlarm, opcodeSetAlarmExplicit);
        }

        void installOpcodes (Interpreter::Interpreter& interpreter)
        {
        	interpreter.installSegment3 (opcodeAIActivate, new OpAiActivate<ImplicitRef>);
        	interpreter.installSegment3 (opcodeAIActivateExplicit, new OpAiActivate<ExplicitRef>);
            interpreter.installSegment3 (opcodeAiTravel, new OpAiTravel<ImplicitRef>);
            interpreter.installSegment3 (opcodeAiTravelExplicit, new OpAiTravel<ExplicitRef>);
            interpreter.installSegment3 (opcodeAiEscort, new OpAiEscort<ImplicitRef>);
            interpreter.installSegment3 (opcodeAiEscortExplicit, new OpAiEscort<ExplicitRef>);
            interpreter.installSegment3 (opcodeAiEscortCell, new OpAiEscortCell<ImplicitRef>);
            interpreter.installSegment3 (opcodeAiEscortCellExplicit, new OpAiEscortCell<ExplicitRef>);
            interpreter.installSegment3 (opcodeAiWander, new OpAiWander<ImplicitRef>);
            interpreter.installSegment3 (opcodeAiWanderExplicit, new OpAiWander<ExplicitRef>);
            interpreter.installSegment3 (opcodeAiFollow, new OpAiFollow<ImplicitRef>);
            interpreter.installSegment3 (opcodeAiFollowExplicit, new OpAiFollow<ExplicitRef>);
            interpreter.installSegment3 (opcodeAiFollowCell, new OpAiFollowCell<ImplicitRef>);
            interpreter.installSegment3 (opcodeAiFollowCellExplicit, new OpAiFollowCell<ExplicitRef>);
            interpreter.installSegment5 (opcodeGetAiPackageDone, new OpGetAiPackageDone<ImplicitRef>);
            interpreter.installSegment5 (opcodeGetAiPackageDoneExplicit, new OpGetAiPackageDone<ExplicitRef>);
            interpreter.installSegment5 (opcodeGetCurrentAiPackage, new OpGetCurrentAIPackage<ImplicitRef>);
            interpreter.installSegment5 (opcodeGetCurrentAiPackageExplicit, new OpGetCurrentAIPackage<ExplicitRef>);
            interpreter.installSegment3 (opcodeGetDetected, new OpGetDetected<ImplicitRef>);
            interpreter.installSegment3 (opcodeGetDetectedExplicit, new OpGetDetected<ExplicitRef>);
            interpreter.installSegment5 (opcodeSetHello, new OpSetHello<ImplicitRef>);
            interpreter.installSegment5 (opcodeSetHelloExplicit, new OpSetHello<ExplicitRef>);
            interpreter.installSegment5 (opcodeSetFight, new OpSetFight<ImplicitRef>);
            interpreter.installSegment5 (opcodeSetFightExplicit, new OpSetFight<ExplicitRef>);
            interpreter.installSegment5 (opcodeSetFlee, new OpSetFlee<ImplicitRef>);
            interpreter.installSegment5 (opcodeSetFleeExplicit, new OpSetFlee<ExplicitRef>);
            interpreter.installSegment5 (opcodeSetAlarm, new OpSetAlarm<ImplicitRef>);
            interpreter.installSegment5 (opcodeSetAlarmExplicit, new OpSetAlarm<ExplicitRef>);
        }
    }
}
