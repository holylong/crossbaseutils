//#include <iostream>
//#include <Windows.h>
//
//
//using namespace std;
//
///*
//	替换/to\
//*/
//void replacePathError(string& strPath)
//{
//	string rep = "/", place = "\\", replace = "\\\\";
//	int pos = strPath.find(rep);
//	while (pos != -1)
//	{
//		strPath.replace(pos, sizeof(rep), place);
//
//		pos = strPath.find(rep);
//	}
//}
//
//void PathRemoveFileSpec(string& strPath)
//{
//	replacePathError(strPath);
//}
//
//BOOL CreateDeepDirectory(LPCTSTR szPath)
//{
//	BOOL bRetCode = FALSE;
//	string strPath = (const char*)szPath;
//
//	if (GetFileAttributes(szPath) != INVALID_FILE_ATTRIBUTES)
//		return TRUE;
//
//	bRetCode = ::CreateDirectory(szPath, NULL);
//	if (!bRetCode && ::GetLastError() != ERROR_ALREADY_EXISTS)
//	{
//		PathRemoveFileSpec(strPath);
//		if (strPath == "")
//			return FALSE;
//
//		bRetCode = CreateDeepDirectory((LPCTSTR)strPath.c_str());
//		if (!bRetCode) return FALSE;
//
//		bRetCode = ::CreateDirectory(szPath, NULL);
//		if (!bRetCode && ::GetLastError() != ERROR_ALREADY_EXISTS)
//			return FALSE;
//	}
//
//	return TRUE;
//}
//
//
//int main(int argc, char* argv[])
//{
//    std::cout << "Hello World!\n";
//	string str = "D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/lib";
//	CreateDeepDirectory((LPCTSTR)str.c_str());
//}
//
//// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
//// 调试程序: F5 或调试 >“开始调试”菜单
//
//// 入门使用技巧: 
////   1. 使用解决方案资源管理器窗口添加/管理文件
////   2. 使用团队资源管理器窗口连接到源代码管理
////   3. 使用输出窗口查看生成输出和其他消息
////   4. 使用错误列表窗口查看错误
////   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
////   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


#include<iostream>
#include<fstream>
#include"windows.h" 
#include "math.h" 
#include<vector>
#include <direct.h>  
using namespace std;

LPWSTR toUnicode11(const char* _str)
{
	LPWSTR _ret;
	int _len = strlen(_str) * 2;

	_ret = new WCHAR[_len];

	MultiByteToWideChar(CP_ACP, 0, _str, -1, _ret, _len);

	return _ret;
}

void  CreateDir(string dir)
{
	if (CreateDirectoryW(toUnicode11(dir.c_str()), 0) == 0)
	{
		//error
		if (string::npos == dir.find('\\'))return;

		int i = dir.size();
		for (; i >= 0; i--)
		{
			if (dir[i] == '\\')break;;

		}
		CreateDir(dir.substr(0, i));
		CreateDirectoryW(toUnicode11(dir.c_str()), 0);
	}

}

void replaceStr(string& path) {
	string rep = "/", place = "\\", replace = "\\\\";
	int pos = path.find(rep);
	while (pos != -1)
	{
		path.replace(pos, rep.length(), place);
		pos = path.find(rep);
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "arguments error, use? w path" << endl;
		return -1;
	}
	string path = argv[1];
	//string str = "D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/lib";
	cout << "path start:" << path.c_str() << endl;
	replaceStr(path);
	cout << "path end:" << path.c_str() << endl;
	CreateDir(path);
	return 0;
}