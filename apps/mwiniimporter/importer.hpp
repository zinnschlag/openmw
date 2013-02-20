/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWINIIMPORTER_IMPORTER
#define MWINIIMPORTER_IMPORTER 1

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <string>
#include <map>
#include <vector>
#include <exception>

#include <components/to_utf8/to_utf8.hpp>

class MwIniImporter {
  public:
    typedef std::map<std::string, std::string> strmap;
    typedef std::map<std::string, std::vector<std::string> > multistrmap;

    MwIniImporter();
    void    setInputEncoding(const ToUTF8::FromType& encoding);
    void    setVerbose(bool verbose);
    multistrmap  loadIniFile(std::string filename);
    multistrmap  loadCfgFile(std::string filename);
    void    merge(multistrmap &cfg, multistrmap &ini);
    void    mergeFallback(multistrmap &cfg, multistrmap &ini);
    void    importGameFiles(multistrmap &cfg, multistrmap &ini);
    void    importArchives(multistrmap &cfg, multistrmap &ini);
    void    writeToFile(boost::iostreams::stream<boost::iostreams::file_sink> &out, multistrmap &cfg);
    
  private:
    void insertMultistrmap(multistrmap &cfg, std::string key, std::string value);
    std::string numberToString(int n);
    std::string toUTF8(const std::string &str);
    bool mVerbose;
    strmap mMergeMap;
    std::vector<std::string> mMergeFallback;
    ToUTF8::FromType mEncoding;
};


#endif
