#ifndef FIND_BACKCODE_H
#define FIND_BACKCODE_H

#include <QWidget>
#include "ui_find_backcode.h"

class find_backcode : public QWidget
{
	Q_OBJECT

public:
	find_backcode(QWidget *parent = 0);
	~find_backcode();

private:
	Ui::find_backcode ui;
	public slots:
	void ok_handle();
	void cancle_handle();

};

#endif // FIND_BACKCODE_H
