//#include "head.h"
#include "SoundTools.h"

//#include <Windows.h>


//-----------------------------------------------------------------------------
// Name: GetWaveFormatFromIndex()
// Desc: Returns 20 different wave formats based on nIndex
//-----------------------------------------------------------------------------
void  tchartochar(const TCHAR *tchar, char *_char)
{
	int length = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, length, NULL, NULL);
}
void CSoundTools::GetWaveFormatFromIndex(int nIndex, WAVEFORMATEX* pwfx)
{
	int iSampleRate = nIndex / 4;
	int iType = nIndex % 4;

	switch (iSampleRate)
	{
	case 0: pwfx->nSamplesPerSec = 48000; break;
	case 1: pwfx->nSamplesPerSec = 44100; break;
	case 2: pwfx->nSamplesPerSec = 22050; break;
	case 3: pwfx->nSamplesPerSec = 11025; break;
	case 4: pwfx->nSamplesPerSec = 8000; break;
	}

	switch (iType)
	{
	case 0: pwfx->wBitsPerSample = 8; pwfx->nChannels = 1; break;
	case 1: pwfx->wBitsPerSample = 16; pwfx->nChannels = 1; break;
	case 2: pwfx->wBitsPerSample = 8; pwfx->nChannels = 2; break;
	case 3: pwfx->wBitsPerSample = 16; pwfx->nChannels = 2; break;
	}

	pwfx->nBlockAlign = pwfx->nChannels * (pwfx->wBitsPerSample / 8);
	pwfx->nAvgBytesPerSec = pwfx->nBlockAlign * pwfx->nSamplesPerSec;
}

void CSoundTools::GetWaveFormatFromIndex(WAVEFORMATEX* pcmwf)
{
	pcmwf->wFormatTag = WAVE_FORMAT_PCM;
	pcmwf->nChannels = 1;
	pcmwf->nSamplesPerSec = 8000;
	pcmwf->nAvgBytesPerSec = 1 * 8000 * 16 / 8;
	pcmwf->nBlockAlign = 16 * 1 / 8;
	pcmwf->wBitsPerSample = 16;
	pcmwf->cbSize = 0;
}
QString CSoundTools::GetAppPath(void)
{
	TCHAR path[MAX_PATH];
	GetCurrentDirectory(1024, path);
	QString fullPath;
	char _path[250];
	tchartochar(path, _path);
	fullPath = QString(QLatin1String(_path));
	//fullPath = QString("%s").arg(_path);
	//QString sp = "\\";
	//int ret = fullPath.lastIndexOf(sp);
	//fullPath = fullPath.left(ret) + "\\";
	return fullPath;
}
QString CSoundTools::GetSystemTime()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	QString retStr;
	//retStr = QString("%4d-%02d-%02d-%02d-%02d-%02d-%03d").arg(sys.wYear).arg(sys.wMonth).arg(sys.wHour).arg(sys.wMinute).arg(sys.wMilliseconds);
	retStr = QString("%1-%2-%3-%4-%5").arg(sys.wYear).arg(sys.wMonth).arg(sys.wHour).arg(sys.wMinute).arg(sys.wMilliseconds);
	
	return retStr;
}
void CSoundTools::WaveZoom(short *buff, int len, int scale)
{
	int i;
	float floatdata;
	for (i = 0; i < len; i++)
	{
		floatdata = (float)(buff[i] * (short)scale);
		if (floatdata <  -32767.5)
		{
			floatdata = -32768;
		}
		else if (floatdata >(FLOAT)32766.5)
		{
			floatdata = 32767;
		}
		buff[i] = (short)floatdata;
	}
}
