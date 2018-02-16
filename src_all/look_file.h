#ifndef LOOK_FILE_H
#define LOOK_FILE_H

#include <QWidget>
#include "ui_look_file.h"

class look_file : public QWidget
{
	Q_OBJECT

public:
	look_file(QWidget *parent = 0);
	void insert_listwidgetitem(QString sender, QString file_name);
	~look_file();
	public slots:
	void download();
	
protected:
	void customEvent(QEvent *event);

private:
	Ui::look_file ui;
};

#endif // LOOK_FILE_H
