/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include <qdialog.h>
#include <components/files/configurationmanager.hpp>

class DataFilesList;
class QDialogButtonBox;

class OpenDialog : public QDialog {
    Q_OBJECT
public:
    OpenDialog(QWidget * parent = 0);
    
    void getFileList(std::vector<boost::filesystem::path>& paths);
private:
    DataFilesList * mFileSelector;
    QDialogButtonBox * buttonBox;
    Files::ConfigurationManager mCfgMgr;
};