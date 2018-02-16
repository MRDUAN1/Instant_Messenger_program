
#include <Windows.h>
#include "WaveWriteFile.h"
#include <vector>

#include <qstring.h>
#include <qbytearray.h>
#include <string>
using namespace std;
QString in;
CWaveWriteFile::CWaveWriteFile(void)
{
	g_pWaveFile = NULL;
}

bool CWaveWriteFile::Init(QString FileName)
{
	FileName = m_SoundTools.GetAppPath();
	FileName += "\\";
	FileName += "sound_re\\";
	FileName += m_SoundTools.GetSystemTime();
	FileName += ".wav";
	in = m_SoundTools.GetSystemTime() + ".wav";
	SAFE_DELETE(g_pWaveFile);
	g_pWaveFile = new CWaveFile;
	if (NULL == g_pWaveFile)
	{
		return false;
	}
	
	m_SoundTools.GetWaveFormatFromIndex(&m_Pcmwf);
	
	//const char*filename = FileName.toLocal8Bit().constData();
	char *temp;
	//char temp[100] = { '\0' };
	QByteArray temp_bytearry = FileName.toLatin1();
	temp = temp_bytearry.data();
	/*const char *filename = temp;
	LPTSTR file = (LPTSTR)(LPCTSTR)filename;*/
	string im(temp);
	char bufff[200] = { '\0' };
	memcpy(bufff, temp, strlen(temp));
	wchar_t* wszResult = new wchar_t[200];
	ZeroMemory(wszResult, 200);
	int j = MultiByteToWideChar(CP_ACP, 0, bufff, -1, wszResult, 200);
	// Load the wave file
	LPTSTR lpstr = wszResult;
	if (FAILED(g_pWaveFile->Open((LPTSTR)lpstr, &m_Pcmwf, WAVEFILE_WRITE)))
	{
		return false;
	}
	return true;
}
bool CWaveWriteFile::Write(char *buf, int len)
{
	UINT dwDataWrote;
	if (FAILED(g_pWaveFile->Write(len, (BYTE*)buf, &dwDataWrote)))
	{
		return false;
	}
	return true;
}
void CWaveWriteFile::EndWrite()
{
	SAFE_DELETE(g_pWaveFile);
}
CWaveWriteFile::~CWaveWriteFile(void)
{
	if (g_pWaveFile)
	{
		EndWrite();
	}
}
