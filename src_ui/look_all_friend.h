#ifndef LOOK_ALL_FRIEND_H
#define LOOK_ALL_FRIEND_H

#include <QWidget>
#include "ui_look_all_friend.h"
#include <qlistwidget.h>
#include <QListWidgetItem>

class look_all_friend : public QWidget
{
	Q_OBJECT

public:
	look_all_friend(QWidget *parent = 0);
	void insert_listwidgetitem(QString);
	~look_all_friend();

private:
	QPixmap pix;
	QString str;
	Ui::look_all_friend ui;
	public slots:
	void selectclicked();
	void ok_clicked();
	void cancle_clicked();
};

#endif // LOOK_ALL_FRIEND_H
