
#include "miscextensions.hpp"

#include <components/compiler/extensions.hpp>

#include <components/interpreter/interpreter.hpp>
#include <components/interpreter/runtime.hpp>
#include <components/interpreter/opcodes.hpp>

#include "../mwworld/class.hpp"

#include "interpretercontext.hpp"
#include "ref.hpp"

namespace MWScript
{
    namespace Misc
    {
        class OpXBox : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    runtime.push (0);
                }
        };

        class OpOnActivate : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    MWWorld::Ptr ptr = context.getReference();

                    runtime.push (context.hasBeenActivated (ptr));
                }
        };

        class OpActivate : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    MWWorld::Ptr ptr = context.getReference();

                    context.executeActivation();
                }
        };

        template<class R>
        class OpLock : public Interpreter::Opcode1
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime, unsigned int arg0)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    Interpreter::Type_Integer lockLevel = 100;

                    if (arg0==1)
                    {
                        lockLevel = runtime[0].mInteger;
                        runtime.pop();
                    }

                    MWWorld::Class::get (ptr).lock (ptr, lockLevel);
                }
        };

        template<class R>
        class OpUnlock : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    MWWorld::Ptr ptr = R()(runtime);

                    MWWorld::Class::get (ptr).unlock (ptr);
                }
        };

        class OpToggleCollisionDebug : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    bool enabled =
                        context.getWorld().toggleRenderMode (MWWorld::World::Render_CollisionDebug);

                    context.report (enabled ?
                        "Collision Mesh Rendering -> On" : "Collision Mesh Rendering -> Off");
                }
        };
        
        class OpToggleWireframe : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    bool enabled =
                        context.getWorld().toggleRenderMode (MWWorld::World::Render_Wireframe);

                    context.report (enabled ?
                        "Wireframe Rendering -> On" : "Wireframe Rendering -> Off");
                }
        };
        
        class OpFadeIn : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    Interpreter::Type_Float time = runtime[0].mFloat;
                    runtime.pop();
                    
                    context.getWorld().getFader()->fadeIn(time);
                }
        };
        
        class OpFadeOut : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    Interpreter::Type_Float time = runtime[0].mFloat;
                    runtime.pop();
                    
                    context.getWorld().getFader()->fadeOut(time);
                }
        };
        
        class OpFadeTo : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    Interpreter::Type_Float alpha = runtime[0].mFloat;
                    runtime.pop();
                    
                    Interpreter::Type_Float time = runtime[0].mFloat;
                    runtime.pop();
                    
                    context.getWorld().getFader()->fadeTo(alpha, time);
                }
        };

        class OpToggleWater : public Interpreter::Opcode0
        {
            public:

                virtual void execute (Interpreter::Runtime& runtime)
                {
                    InterpreterContext& context =
                        static_cast<InterpreterContext&> (runtime.getContext());

                    context.getWorld().toggleWater();
                }
        };

        const int opcodeXBox = 0x200000c;
        const int opcodeOnActivate = 0x200000d;
        const int opcodeActivate = 0x2000075;
        const int opcodeLock = 0x20004;
        const int opcodeLockExplicit = 0x20005;
        const int opcodeUnlock = 0x200008c;
        const int opcodeUnlockExplicit = 0x200008d;
        const int opcodeToggleCollisionDebug = 0x2000132;
        const int opcodeToggleWireframe = 0x200013b;
        const int opcodeFadeIn = 0x200013c;
        const int opcodeFadeOut = 0x200013d;
        const int opcodeFadeTo = 0x200013e;
        const int opcodeToggleWater = 0x2000144;

        void registerExtensions (Compiler::Extensions& extensions)
        {
            extensions.registerFunction ("xbox", 'l', "", opcodeXBox);
            extensions.registerFunction ("onactivate", 'l', "", opcodeOnActivate);
            extensions.registerInstruction ("activate", "", opcodeActivate);
            extensions.registerInstruction ("lock", "/l", opcodeLock, opcodeLockExplicit);
            extensions.registerInstruction ("unlock", "", opcodeUnlock, opcodeUnlockExplicit);
            extensions.registerInstruction ("togglecollisionboxes", "", opcodeToggleCollisionDebug);
            extensions.registerInstruction ("togglecollisiongrid", "", opcodeToggleCollisionDebug);
            extensions.registerInstruction ("tcb", "", opcodeToggleCollisionDebug);
            extensions.registerInstruction ("tcg", "", opcodeToggleCollisionDebug);
            extensions.registerInstruction ("twf", "", opcodeToggleWireframe);
            extensions.registerInstruction ("togglewireframe", "", opcodeToggleWireframe);
            extensions.registerInstruction ("fadein", "f", opcodeFadeIn);
            extensions.registerInstruction ("fadeout", "f", opcodeFadeOut);
            extensions.registerInstruction ("fadeto", "ff", opcodeFadeTo);
            extensions.registerInstruction ("togglewater", "", opcodeToggleWater);
            extensions.registerInstruction ("twa", "", opcodeToggleWater);
        }

        void installOpcodes (Interpreter::Interpreter& interpreter)
        {
            interpreter.installSegment5 (opcodeXBox, new OpXBox);
            interpreter.installSegment5 (opcodeOnActivate, new OpOnActivate);
            interpreter.installSegment5 (opcodeActivate, new OpActivate);
            interpreter.installSegment3 (opcodeLock, new OpLock<ImplicitRef>);
            interpreter.installSegment3 (opcodeLockExplicit, new OpLock<ExplicitRef>);
            interpreter.installSegment5 (opcodeUnlock, new OpUnlock<ImplicitRef>);
            interpreter.installSegment5 (opcodeUnlockExplicit, new OpUnlock<ExplicitRef>);
            interpreter.installSegment5 (opcodeToggleCollisionDebug, new OpToggleCollisionDebug);
            interpreter.installSegment5 (opcodeToggleWireframe, new OpToggleWireframe);
            interpreter.installSegment5 (opcodeFadeIn, new OpFadeIn);
            interpreter.installSegment5 (opcodeFadeOut, new OpFadeOut);
            interpreter.installSegment5 (opcodeFadeTo, new OpFadeTo);
            interpreter.installSegment5 (opcodeToggleWater, new OpToggleWater);
        }
    }
}
