#ifndef CHATTING_H
#define CHATTING_H

#include <QWidget>
#include <qtimer.h>
#include <qfile.h>
#include <qwebengineview.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qwebenginepage.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

class chatting : public QWidget
{
	Q_OBJECT

public:
	chatting(QWidget *parent);
	~chatting();

	void on_pushButton_clicked();
	void disTime();

	void on_pushButton_2_clicked();
	void addFace(QString text);

private:
	void sendMsgShow(QString msg);
	void revMsgShow(QString msg);

	QTimer *m_timer;
	bool disFlag;
	bool faceFormFlag;
	QWebEngineView *webView;
	QLineEdit *lineEdit;
	public slots:
	void on_pushButton_clicked();

	
};

#endif // CHATTING_H
