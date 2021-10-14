#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

string getFileName(const string& name){
   char path_buffer[_MAX_PATH];  
   char drive[_MAX_DRIVE];  
   char dir[_MAX_DIR];  
   char fname[_MAX_FNAME];  
   char ext[_MAX_EXT]; 
  char* szPath = const_cast<char*>(name.c_str());
   while(szPath[strlen(szPath) - 1] == '\\' || szPath[strlen(szPath) - 1] == '/'){
       szPath[strlen(szPath) - 1] = '\0';
   }

    _splitpath(szPath, drive, dir, fname, ext);
    cout << "drive:" << drive << " dir:" << dir << " fname:" << fname << " ext:" << ext << endl; 
    return string(fname) + string(ext);
}

/**
 *   WinExec("cmd /c del 1.txt",SW_HIDE);
 *   system("echo 123");
 *   system("echo 123 > 1.txt");
 *   system("del 1.txt");
 */
int main(int argc, char* argv[]){
    cout << "movethis enter" << endl;

    if(argc <= 1){
        cout << "please input some argments" << endl;
        return -1;
    }

    char command[1024];
    for(int i = 1; i < argc; i++){
        memcpy(command, "\0", 1024);
        if(GetFileAttributes(argv[i])&FILE_ATTRIBUTE_DIRECTORY){
           string name = getFileName(argv[i]);
           stringstream ss;
           ss << "xcopy " << argv[i] << " " << name << " /E/C/F/H/Y/I";
           string tpCommand = ss.str();
           system(tpCommand.c_str());
           ss.clear();
           ss.str("");
           ss << "rd /s/q " << argv[i];
           tpCommand = ss.str();
           cout << "tpCommand:" << tpCommand.c_str() << endl;
           system(tpCommand.c_str());
        }else{
            sprintf(command, "copy %s", argv[i]);
            cout << "command:" << command << endl;
            system(command);
            memcpy(command, "\0", 1024);
            sprintf(command, "del %s", argv[i]);
            system(command);
        }
        //system("xcopy H:\ndkgames\josm josm /E/C/F/H/Y/I");
    }

    cout << "movethis exit" << endl;
    return 0;
}