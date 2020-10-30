#ifndef QFILECOPYIMP_H
#define QFILECOPYIMP_H
#include <QString>
#include <vector>

enum COPY_ERROR{
    COPY_ok,
    COPY_error_last_is_file,
    COPY_error_unknow
};

class QFileCopyImp
{
public:
    QFileCopyImp();

    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);

    COPY_ERROR copyMultiFile(std::vector<QString> arrFilesOrDir, bool coverFileIfExist);
};

#endif // QFILECOPYIMP_H
