#include <qdialog.h>
#include <components/files/configurationmanager.hpp>

class DataFilesList;
class QDialogButtonBox;
class QComboBox;
class OpenFileProxyModel;

class OpenDialog : public QDialog {
    Q_OBJECT
public:
    OpenDialog(QWidget * parent = 0);
    
    void getFileList(std::vector<boost::filesystem::path>& paths);
private:
    DataFilesList * mFileSelector;
    QDialogButtonBox * mButtonBox;
    QComboBox * mEditedFileSelector;
    OpenFileProxyModel * mFilesProxyModel;
    Files::ConfigurationManager mCfgMgr;
};
