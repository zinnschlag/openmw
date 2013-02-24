#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QSortFilterProxyModel>
#include <QLabel>
#include <QPushButton>

#include "../../model/doc/openfileproxymodel.hpp"

#include <components/fileorderlist/datafileslist.hpp>

#include "opendialog.hpp"

OpenDialog::OpenDialog(QWidget * parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    mFileSelector = new DataFilesList(mCfgMgr, this);
    layout->addWidget(mFileSelector);
    
    //FIXME - same as DataFilesPage::setupDataFiles
    // We use the Configuration Manager to retrieve the configuration values
    boost::program_options::variables_map variables;
    boost::program_options::options_description desc;
    
    desc.add_options()
    ("data", boost::program_options::value<Files::PathContainer>()->default_value(Files::PathContainer(), "data")->multitoken())
    ("data-local", boost::program_options::value<std::string>()->default_value(""))
    ("fs-strict", boost::program_options::value<bool>()->implicit_value(true)->default_value(false))
    ("encoding", boost::program_options::value<std::string>()->default_value("win1252"));
    
    boost::program_options::notify(variables);
    
    mCfgMgr.readConfiguration(variables, desc);
    
    Files::PathContainer mDataDirs, mDataLocal;
    if (!variables["data"].empty()) {
        mDataDirs = Files::PathContainer(variables["data"].as<Files::PathContainer>());
    }
    
    std::string local = variables["data-local"].as<std::string>();
    if (!local.empty()) {
        mDataLocal.push_back(Files::PathContainer::value_type(local));
    }
    
    mCfgMgr.processPaths(mDataDirs);
    mCfgMgr.processPaths(mDataLocal);
    
    // Set the charset for reading the esm/esp files
    QString encoding = QString::fromStdString(variables["encoding"].as<std::string>());
    
    Files::PathContainer dataDirs;
    dataDirs.insert(dataDirs.end(), mDataDirs.begin(), mDataDirs.end());
    dataDirs.insert(dataDirs.end(), mDataLocal.begin(), mDataLocal.end());
    mFileSelector->setupDataFiles(dataDirs, encoding);
    
    QHBoxLayout *selectedFileLayout = new QHBoxLayout();
    QLabel *selectedFileLabel = new QLabel(tr("Selected File: "), this);
    selectedFileLayout->addWidget(selectedFileLabel);
    
    mEditedFileSelector = new QComboBox(this);
    mEditedFileSelector->setInsertPolicy(QComboBox::InsertAtBottom);
    connect(mEditedFileSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(enableOpenButton()));
    
    mFilesProxyModel = new OpenFileProxyModel(this);
    mFilesProxyModel->setDynamicSortFilter(true);
    mFilesProxyModel->setSourceModel(mFileSelector->model());
    mEditedFileSelector->setModel(mFilesProxyModel);
    connect(mFilesProxyModel, SIGNAL(layoutChanged()), mEditedFileSelector, SLOT(update()));
    //signal currentIndexChanged() isn't allways emited when currentIndex changes, workaround for this
    connect(mFilesProxyModel, SIGNAL(layoutChanged()), this, SLOT(enableOpenButton()));
    selectedFileLayout->addWidget(mEditedFileSelector, 1); //strech mEditedFileSelector   
    layout->addLayout(selectedFileLayout);
    
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    connect(mButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(mButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
    mButtonBox->button(QDialogButtonBox::Open)->setEnabled(false);
    layout->addWidget(mButtonBox);
    
    setLayout(layout);
    setWindowTitle(tr("Open"));
}

void OpenDialog::getFileList(std::vector<boost::filesystem::path>& paths)
{
    mFileSelector->selectedFiles(paths, mEditedFileSelector->currentText());
}

void OpenDialog::enableOpenButton()
{
    if (mEditedFileSelector->currentIndex() != -1)
        mButtonBox->button(QDialogButtonBox::Open)->setEnabled(true);
    else
        mButtonBox->button(QDialogButtonBox::Open)->setEnabled(false);
}
