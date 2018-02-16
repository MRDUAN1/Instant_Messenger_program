#pragma once
#include "qq_main.h"
#include "register_dialog.h"
#include <qmessagebox.h>
class signal_connect
{
public:
	signal_connect(qq_main *qq);
	~signal_connect();
signals:
	void register_successful();
	void register_fail();
	void login_successful();
	void login_fail();
	void quit_successful();
	void quit_fail();
	void change_passwd_successful();
	void change_passwd_fail();
	void change_other_successful();
	void change_other_fail();
	void change_status_successful();
	void change_status_fail();
public slots:
void handle_register_successful();
void handle_register_fail();
void handle_login_successful();
void handle_login_fail();
void handle_quit_successful();
void handle_quit_fail();
void handle_change_passwd_successful();
void handle_change_passwd_fail();
void handle_change_other_successful();
void handle_change_other_fail();
void handle_change_status_successful();
void handle_change_status_fail();
private:
	qq_main *qq;


};

