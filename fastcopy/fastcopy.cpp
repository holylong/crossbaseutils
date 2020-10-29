// fastcopy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h> 
#include <tchar.h>


//

//cmd.exe /C "cd /D D:\WorkStation\gohome\janus\janus-mobile-sdk\platforms\android\janus-client\.externalNativeBuild\cmake\debug\armeabi-v7a\third_party\boringssl\src\boringssl_proj-build && winmkdir D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/lib && copy D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/boringssl/src/boringssl_proj-build/ssl/libssl.a D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/boringssl/src/boringssl_proj-build/crypto/libcrypto.a D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/lib && winmkdir D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/include && copy D:/WorkStation/gohome/janus/janus-mobile-sdk/third_party/boringssl/include/openssl D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/include && D:\Android\Sdk\cmake\3.10.2.4988404\bin\cmake.exe -E touch D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/boringssl/src/boringssl_proj-stamp/boringssl_proj-install"

//copy multi files and copy multi dir and files
//copy D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/boringssl/src/boringssl_proj-build/ssl/libssl.a D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/boringssl/src/boringssl_proj-build/crypto/libcrypto.a D:/WorkStation/gohome/janus/janus-mobile-sdk/platforms/android/janus-client/.externalNativeBuild/cmake/debug/armeabi-v7a/third_party/lib
int main(int argc, char* argv[]) {
	WIN32_FIND_DATA File;
	HANDLE hSearch;

	TCHAR SourcePath[_MAX_PATH];
	TCHAR SourceDrive[_MAX_DRIVE];
	TCHAR SourceDir[_MAX_DIR];
	TCHAR SourceFname[_MAX_FNAME];
	TCHAR SourceExt[_MAX_EXT];

	TCHAR DestPath[_MAX_PATH];
	TCHAR DestDrive[_MAX_DRIVE];
	TCHAR DestDir[_MAX_DIR];

	LPCTSTR lpszFindPattern = TEXT("D:\\1\\123.txt");

	_tsplitpath_s(_T("D:\\1\\"), SourceDrive, _MAX_DRIVE, SourceDir, _MAX_DIR, NULL, 0, NULL, 0);
	_tsplitpath_s(_T("D:\\2\\"), DestDrive, _MAX_DRIVE, DestDir, _MAX_DIR, NULL, 0, NULL, 0);

	hSearch = FindFirstFile(lpszFindPattern, &File);
	if (hSearch != INVALID_HANDLE_VALUE) {
		do {
			_tsplitpath_s(File.cFileName, NULL, 0, NULL, 0, SourceFname, _MAX_FNAME, SourceExt, _MAX_EXT);

			_tmakepath_s(SourcePath, _MAX_PATH, SourceDrive, SourceDir, SourceFname, SourceExt);
			_tmakepath_s(DestPath, _MAX_PATH, DestDrive, DestDir, SourceFname, SourceExt);

			BOOL  err = CopyFile(SourcePath, DestPath, FALSE);
			int err1 = GetLastError();

			int x = 0;
		} while (FindNextFile(hSearch, &File));

		FindClose(hSearch);
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
