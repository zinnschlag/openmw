/*
  Test of the BSAFile class

  This test requires that data/Morrowind.bsa exists in the root
  directory of OpenMW.
 */

#include <iostream>
#include "../bsa_file.hpp"

using namespace std;
using namespace Bsa;

#define TEST_BSA_FILE_PATH "../../../data/Morrowind.bsa"

BSAFile bsa;

void find(const char* file)
{
  cout << "Does file '" << file << "' exist?\n  ";
  if(bsa.exists(file))
    {
      cout << "Yes.\n  ";
      cout << bsa.getFile(file)->size() << " bytes\n";
    }
  else cout << "No.\n";
}

int main(int argc, char** argv)
{
  std::string filename = "meshes\\r\\xnetch_betty.nif";
  if (argc > 1)
  {
    filename = "";
    for (int i = 1; i < argc; i++)
    {
      filename += argv[i];
      if (i+1 < argc)
        filename += "\\";
    }
  }

  cout << "Reading Morrowind.bsa\n";
  bsa.open(TEST_BSA_FILE_PATH);

  const BSAFile::FileList &files = bsa.getList();

  cout << "First 10 files in archive:\n";
  for(int i=0; i<10; i++)
    cout << "  " << files[i].name
         << " (" << files[i].fileSize << " bytes @"
         << files[i].offset << ")\n";

  find(filename.c_str());
  find("humdrum");
}
