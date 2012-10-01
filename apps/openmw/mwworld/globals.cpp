
#include "globals.hpp"

#include <stdexcept>

#include <components/esm_store/store.hpp>

namespace MWWorld
{
    Globals::Collection::const_iterator Globals::find (const std::string& name) const
    {
        Collection::const_iterator iter = mVariables.find (name);
            
        if (iter==mVariables.end())
            throw std::runtime_error ("unknown global variable: " + name);
            
        return iter;    
    }

    Globals::Collection::iterator Globals::find (const std::string& name)
    {
        Collection::iterator iter = mVariables.find (name);
            
        if (iter==mVariables.end())
            throw std::runtime_error ("unknown global variable: " + name);
            
        return iter;    
    }

    Globals::Globals (const ESMS::ESMStore& store)
    {
        for (ESMS::RecListT<ESM::Global>::MapType::const_iterator iter
            (store.globals.list.begin()); iter != store.globals.list.end(); ++iter)
        {
            char type = ' ';
            Data value;
        
            switch (iter->second.mType)
            {
                case ESM::VT_Short:
                    
                    type = 's';
                    value.mShort = *reinterpret_cast<const Interpreter::Type_Float *> (
                        &iter->second.mValue);
                    break;
                    
                case ESM::VT_Int:
                
                    type = 'l';
                    value.mLong = *reinterpret_cast<const Interpreter::Type_Float *> (
                        &iter->second.mValue);
                    break;
                    
                case ESM::VT_Float:
                
                    type = 'f';
                    value.mFloat = *reinterpret_cast<const Interpreter::Type_Float *> (
                        &iter->second.mValue);
                    break;
                    
                default:
                
                    throw std::runtime_error ("unsupported global variable type");
            }            

            mVariables.insert (std::make_pair (iter->first, std::make_pair (type, value)));
        }
        
        if (mVariables.find ("dayspassed")==mVariables.end())
        {
            // vanilla Morrowind does not define dayspassed.
            Data value;
            value.mLong = 0;
            
            mVariables.insert (std::make_pair ("dayspassed", std::make_pair ('l', value)));
        }
    }

    const Globals::Data& Globals::operator[] (const std::string& name) const
    {
        Collection::const_iterator iter = find (name);
            
        return iter->second.second;
    }

    Globals::Data& Globals::operator[] (const std::string& name)
    {
        Collection::iterator iter = find (name);
            
        return iter->second.second;
    }
    
    void Globals::setInt (const std::string& name, int value)
    {
        Collection::iterator iter = find (name);
        
        switch (iter->second.first)
        {
            case 's': iter->second.second.mShort = value; break;
            case 'l': iter->second.second.mLong = value; break;
            case 'f': iter->second.second.mFloat = value; break;
            
            default: throw std::runtime_error ("unsupported global variable type");
        }
    }
    
    void Globals::setFloat (const std::string& name, float value)
    {
        Collection::iterator iter = find (name);

        switch (iter->second.first)
        {
            case 's': iter->second.second.mShort = value; break;
            case 'l': iter->second.second.mLong = value; break;
            case 'f': iter->second.second.mFloat = value; break;

            default: throw std::runtime_error ("unsupported global variable type");
        }        
    }
    
    int Globals::getInt (const std::string& name) const
    {
        Collection::const_iterator iter = find (name);

        switch (iter->second.first)
        {
            case 's': return iter->second.second.mShort;
            case 'l': return iter->second.second.mLong;
            case 'f': return iter->second.second.mFloat;

            default: throw std::runtime_error ("unsupported global variable type");
        }                
    }
        
    float Globals::getFloat (const std::string& name) const
    {
        Collection::const_iterator iter = find (name);
    
        switch (iter->second.first)
        {
            case 's': return iter->second.second.mShort;
            case 'l': return iter->second.second.mLong;
            case 'f': return iter->second.second.mFloat;

            default: throw std::runtime_error ("unsupported global variable type");
        }    
    }
    
    char Globals::getType (const std::string& name) const
    {
        Collection::const_iterator iter = mVariables.find (name);
        
        if (iter==mVariables.end())
            return ' ';
            
        return iter->second.first;
    }
}

