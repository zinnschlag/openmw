#ifndef GAME_SCRIPT_EXTENSIONS_H
#define GAME_SCRIPT_EXTENSIONS_H

namespace Compiler
{
    class Extensions;
}

namespace Interpreter
{
    class Interpreter;
}

namespace MWScript
{
    void registerExtensions (Compiler::Extensions& extensions, bool consoleOnly = false);
    ///< \param extensions 
    /// \param consoleOnly include console only extensions

    void installOpcodes (Interpreter::Interpreter& interpreter, bool consoleOnly = false);
    ///< \param interpreter 
    /// \param consoleOnly include console only opcodes
}

#endif
