#ifndef DETAILFRIENDSS_H
#define DETAILFRIENDSS_H

#include "ui_detailfriendss.h"

#include "widget_.h"
#include <QWidget>
#include <qstring.h>

class widget_;
class detailfriendss : public QWidget
{
	Q_OBJECT

public:
	detailfriendss(QWidget *parent = 0);
	/*usr1 birthday,usr2 telphone, other_use mymaxim, usr4 image, random name*/
	int change_(QString name, QString telephone, QString birthday_, QString mymaxim_, string name_, QString
		 account, QString image_name);
	~detailfriendss();

private:
	Ui::detailfriendss ui;
	QPoint windowPos, mousePos, dPos;
protected:
	void paintEvent(QPaintEvent *event);
	void detailfriendss::mousePressEvent(QMouseEvent *event);
	void detailfriendss::mouseMoveEvent(QMouseEvent *event);
};

#endif // DETAILFRIENDSS_H
