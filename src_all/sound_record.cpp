#include "sound_record.h"
#include <qrect.h>



sound_record::sound_record(QWidget *parent)
	: QMainWindow(parent)
{

}

sound_record::~sound_record()
{
	
}
void sound_record::start_()
{
	m_cap_ado.Open();
	m_WaveWriteFile.Init();
	m_cap_ado.GrabAudioFrames(TRUE, this);
}
void sound_record::end_()
{
	m_cap_ado.GrabAudioFrames(FALSE, NULL);
	m_WaveWriteFile.EndWrite();
	m_cap_ado.Close();
}

void sound_record::AdoFrameData(BYTE* pBuffer, long lBufferSize)
{
	m_WaveWriteFile.Write((char*)pBuffer, lBufferSize);
}
#include "moc_sound_record.cpp"


