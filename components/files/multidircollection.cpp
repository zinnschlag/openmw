
#include "multidircollection.hpp"

#include <cctype>

#include <algorithm>
#include <stdexcept>

#include <boost/filesystem.hpp>

namespace Files
{
    struct NameEqual
    {
        bool mStrict;

        NameEqual (bool strict) : mStrict (strict) {}

        bool operator() (const std::string& left, const std::string& right) const
        {
            if (mStrict)
                return left==right;

            std::size_t len = left.length();

            if (len!=right.length())
                return false;

            for (std::size_t i=0; i<len; ++i)
            {
                char l = std::tolower (left[i]);
                char r = std::tolower (right[i]);

                if (l!=r)
                    return false;
            }

            return true;
        }
    };

    MultiDirCollection::MultiDirCollection (const std::vector<boost::filesystem::path>& directories,
        const std::string& extension, bool foldCase)
    : mFiles (NameLess (!foldCase))
    {
        NameEqual equal (!foldCase);

        for (std::vector<boost::filesystem::path>::const_iterator iter = directories.begin();
            iter!=directories.end(); ++iter)
        {
            boost::filesystem::path dataDirectory = *iter;

            for (boost::filesystem::directory_iterator iter (dataDirectory);
                iter!=boost::filesystem::directory_iterator(); ++iter)
            {
                boost::filesystem::path path = *iter;

// TODO: Remove
#if !defined(BOOST_FILESYSTEM_VERSION) || BOOST_FILESYSTEM_VERSION == 2
                if (!equal (extension, path.extension()))
                    continue;

                std::string filename = path.filename();
#else
                if (!equal (extension, path.extension().string()))
                    continue;

                std::string filename = path.filename().string();
#endif

                TIter result = mFiles.find (filename);

                if (result==mFiles.end())
                {
                    mFiles.insert (std::make_pair (filename, path));
                }
                else if (result->first==filename)
                {
                    mFiles[filename] = path;
                }
                else
                {
                    // handle case folding
                    mFiles.erase (result->first);
                    mFiles.insert (std::make_pair (filename, path));
                }
            }
        }
    }

    boost::filesystem::path MultiDirCollection::getPath (const std::string& file) const
    {
        TIter iter = mFiles.find (file);

        if (iter==mFiles.end())
            throw std::runtime_error ("file " + file + " not found");

        return iter->second;
    }

    MultiDirCollection::TIter MultiDirCollection::begin() const
    {
        return mFiles.begin();
    }

    MultiDirCollection::TIter MultiDirCollection::end() const
    {
        return mFiles.end();
    }
}
