#pragma once
//#include "head.h"
#include "WaveFile.h"
#include "SoundTools.h"
#include <qstring.h>
#include <qfile.h>


class CWaveWriteFile
{
public:
	CWaveWriteFile(void);
public:
	~CWaveWriteFile(void);
public:
	bool Init(QString FileName = "1.wav");
	bool Write(char *buf, int len);
	void EndWrite();
public:
	CWaveFile		*g_pWaveFile;
	WAVEFORMATEX	m_Pcmwf;
	CSoundTools		m_SoundTools;
};
