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
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif
#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ��������Ϊ�ʺ� Windows Me ����߰汾����Ӧֵ��
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
