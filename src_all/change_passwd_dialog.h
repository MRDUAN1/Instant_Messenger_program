#ifndef CHANGE_PASSWD_DIALOG_H
#define CHANGE_PASSWD_DIALOG_H

#include <QWidget>
#include "ui_change_passwd_dialog.h"

class change_passwd_dialog : public QWidget
{
	Q_OBJECT

public:
	change_passwd_dialog(QWidget *parent = 0, bool is_protect = false);
	~change_passwd_dialog();
	public slots:
	void ok_handle();
	void cancle_handle();

private:
	Ui::change_passwd_dialog ui;
	bool is_protect;
};

#endif // CHANGE_PASSWD_DIALOG_H
