/*
  Runs NIFFile through all the NIFs in Morrowind.bsa.
  Uses BSA archive handler for OGRE.
*/

#include <iostream>
#include <Ogre.h>
#include <components/bsa/bsa_archive.hpp>
#include <components/bsa/bsa_file.hpp>
#include <components/misc/stringops.hpp>
#include "../nif_file.hpp"

#define TEST_BSA_FILE_PATH "../../../data/Morrowind.bsa"

using namespace Ogre;
using namespace Bsa;
using namespace Nif;

bool strEndsWith(const char *str, const char *suffix);

int main(int argc, char **args)
{
    BSAFile bsa;
    std::cout << "Reading Morrowind.bsa\n";
    bsa.open(TEST_BSA_FILE_PATH);

    // Set up OGRE Root
    Root *root = new Root("","","");

    // Add the BSA
    Bsa::addBSA(TEST_BSA_FILE_PATH);

    const BSAFile::FileList &files = bsa.getList();

    for(int i=0; i<files.size(); i++)
    {
        const std::string name = files[i].name;
        if(!Misc::ends(name.c_str(), ".nif")) continue;

        std::cout << "Found \"" << name << "\". Parsing...";
        boost::shared_ptr<NIFFile> nif_ptr = NIFFile::create(name);
        std::cout << " Done." << std::endl;

        /* This good old method doesn't work any more. */
        //std::cout << "Decoding " << n << std::endl;
        //NIFFile nif(bsa.getFile(n), n);
    }
}
