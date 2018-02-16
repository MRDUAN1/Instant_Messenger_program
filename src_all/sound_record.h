#ifndef SOUND_RECORD_H
#define SOUND_RECORD_H
//#include "head.h"
#pragma once
#include <QtWidgets/QMainWindow>
//#include "ui_sound_record.h"
#include <qpushbutton.h>
#include "DSoundIn.h"
#include "WaveWriteFile.h"



class sound_record : public QMainWindow, public CAdoFrameHandler
{
	Q_OBJECT

public:
	sound_record(QWidget *parent = 0);
	void start_();
	void end_();
	void AdoFrameData(BYTE* pBuffer, long lBufferSize);
	~sound_record();
	

private:
	//Ui::sound_recordClass ui;
	//QPushButton *start;
	//QPushButton *end;


	
	
protected:
	CDSoundIn   m_cap_ado; // 这个对象就是用来采集音频数据的
	CWaveWriteFile m_WaveWriteFile;
};

//#include "moc_sound_record.cpp"

#endif // SOUND_RECORD_H
