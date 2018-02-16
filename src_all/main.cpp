#include "qq_main.h"
#include <QtWidgets/QApplication>
#include <Wincrypt.h>
//#include <afxwin.h>

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif
#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将它更改为适合 Windows Me 或更高版本的相应值。
#endif
#pragma comment(lib,"crypt32")
#pragma comment(lib, "libprotobuf.lib")
//#pragma comment(lib, "libprotoc.lib")
#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "libevent_extras.lib") 
#pragma comment(lib, "libevent_core.lib") 
#pragma comment (lib,"Advapi32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"ole32.lib")
#pragma warning(disable : 4099)

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	QApplication::addLibraryPath("./plugins");
	qq_main w;
	w.show();
	return a.exec();
}
