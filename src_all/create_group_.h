#ifndef CREATE_GROUP__H
#define CREATE_GROUP__H

#include <QWidget>
#include <string>
using namespace std;
#include "ui_create_group_.h"


class create_group_ : public QWidget
{
	Q_OBJECT

public:
	create_group_(QString str, int i, QWidget *parent = 0, string id = "0");
	void set_account(QString id)
	{
		account = id;
	}
	~create_group_();

private:
	Ui::create_group_ ui;
	QString GroupName;
	int h;
	QString account;
	string id;
	private slots:
	void ok_handle();
	void cancle_handle();
	

};

#endif // CREATE_GROUP__H
