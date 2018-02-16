#pragma once
#include <Windows.h>
#include <MMSystem.h>
#include <qstring.h>

class CSoundTools
{
public:
	void GetWaveFormatFromIndex(int nIndex, WAVEFORMATEX* pwfx);
	void GetWaveFormatFromIndex(WAVEFORMATEX* pcmwf);
	QString GetAppPath();
	QString GetSystemTime();
	//”Ô“Ù–≈∫≈∑≈¥Û
	void WaveZoom(short *buff, int len, int scale);
};