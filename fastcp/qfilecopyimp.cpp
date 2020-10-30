#include "qfilecopyimp.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

//拷贝多个文件夹或者文件
COPY_ERROR QFileCopyImp::copyMultiFile(std::vector<QString> arrFilesOrDir, bool coverFileIfExist)
{
    /// 参数个数2
    /// 判断第一个目标是否是文件，第二个是文件夹， 将目标拷贝到文件夹
    /// 第一个是文件  第二个也是文件， 拷贝覆盖或者是返回文件存在
    /// 第一个是文件夹第二个也是文件夹，将文件夹 拷贝到第二个文件夹 内
    ///
    /// 参数个数3个 及 以上
    /// 判断最后一个目标是否是 文件夹，如果不是就报错，如果是就一次 把前面的每个目标 拷贝到最后一个 文件夹里
    if(arrFilesOrDir.size() == 2){
        QFileInfo fileInfoSrc(arrFilesOrDir[0]);
        QFileInfo fileInfoDst(arrFilesOrDir[1]);
        qDebug() << arrFilesOrDir[0];
        qDebug() << arrFilesOrDir[1];
        if(fileInfoSrc.isFile()){
            copyFileToPath(arrFilesOrDir[0], arrFilesOrDir[1], coverFileIfExist);
        }else{
            copyDirectoryFiles(arrFilesOrDir[0], arrFilesOrDir[1], coverFileIfExist);
        }
    }else{
        QFileInfo fileInfoDst(arrFilesOrDir[arrFilesOrDir.size() - 1]);
        if(fileInfoDst.exists()){
            for(size_t i = 0; i < arrFilesOrDir.size() - 1; i++){
                qDebug() << arrFilesOrDir[i];
                qDebug() << arrFilesOrDir[arrFilesOrDir.size() - 1];
                QFileInfo fileInfoSrc(arrFilesOrDir[i]);
                if(fileInfoSrc.isFile()){
                    if(copyFileToPath(arrFilesOrDir[i], arrFilesOrDir[arrFilesOrDir.size() - 1], coverFileIfExist))
                        qDebug() << "copy ok";
                    else
                        qDebug() << "copy error";
                    qDebug() << "copy file ok";
                }else{
                    copyDirectoryFiles(arrFilesOrDir[i], arrFilesOrDir[arrFilesOrDir.size() - 1], coverFileIfExist);
                    qDebug() << "copy dir ok";
                }
            }
        }
    }
    qDebug() << "copy all file ok";
    return COPY_ok;
}


QFileCopyImp::QFileCopyImp()
{

}

//拷贝文件：
bool QFileCopyImp::copyFileToPath(QString sourceFilePath ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceFilePath == toDir){
        return true;
    }
    if (!QFile::exists(sourceFilePath)){
        return false;
    }

    ///判断是否是文件夹
    QFileInfo fileInfo(toDir);
    if(fileInfo.exists()){
        if(fileInfo.isDir()){
            QFileInfo filesrc(sourceFilePath);
            QString strName = filesrc.fileName();

            QString fullPath = toDir;
            fullPath += "/";
            fullPath += strName;

            QDir *createfile = new QDir;
            bool exist = createfile->exists(fullPath);
            if (exist){
                if(coverFileIfExist){
                    if(createfile->remove(fullPath))
                        qDebug() << "remove ok";
                    else
                        qDebug() << "remove error";
                }
            }else{
                qDebug() << "file not exists";
            }

            if(!QFile::copy(sourceFilePath, fullPath))
            {
                qDebug() << "copy file error";
                return false;
            }
        }else{
            QString fullPath = toDir;
            QDir *createfile = new QDir;
            bool exist = createfile->exists(fullPath);
            if (exist){
                if(coverFileIfExist){
                    if(createfile->remove(fullPath))
                        qDebug() << "remove ok";
                    else
                        qDebug() << "remove error";
                }
            }else{
                qDebug() << "file not exists";
            }

            if(!QFile::copy(sourceFilePath, fullPath))
            {
                qDebug() << "copy file error";
                return false;
            }
        }
    }

    return true;
}

//拷贝文件夹：
bool QFileCopyImp::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}
