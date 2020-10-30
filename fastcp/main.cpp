#include <QCoreApplication>
#include <QDebug>
#include"qfilecopyimp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    if(argc<=2){
        qDebug() << "input arguments error\n"
                 <<  "please use=> fastcp arg1 arg2 ...";
        return -1;
    }

    QFileCopyImp fastcp;
    std::vector<QString> arrFiles;
    for(int i = 1; i < argc; i++)
        arrFiles.push_back(argv[i]);
    fastcp.copyMultiFile(arrFiles, true);

    return 0;
}
