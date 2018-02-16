#ifndef QTLOGING_H
#define QTLOGING_H

#include <QWidget>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qvector.h>
#include <qtimer.h>
#include <qlabel.h>

class qtloging : public QWidget
{
	Q_OBJECT

public:
	qtloging(QWidget *parent);
	~qtloging();
	void paintEvent(QPaintEvent *event);
	public slots:
	void timeout_handle();

private:
	QVector<QPixmap>vector_pix;
	int height_;
	int width_;
	QLabel *label;
	QRect rect;
	int i;
	
	
};

#endif // QTLOGING_H
