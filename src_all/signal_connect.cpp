#include "signal_connect.h"


signal_connect::signal_connect(qq_main*hp)
{
	qq = hp;
}


signal_connect::~signal_connect()
{
}
void signal_connect::handle_register_successful()
{
	QMessageBox::information(qq, "×¢²á³É¹¦", "¹§Ï²Äú£¬×¢²á³É¹¦");

}
void signal_connect::handle_register_fail();
void signal_connect::handle_login_successful();
void signal_connect::handle_login_fail();
void signal_connect::handle_quit_successful();
void signal_connect::handle_quit_fail();
void signal_connect::handle_change_passwd_successful();
void signal_connect::handle_change_passwd_fail();
void signal_connect::handle_change_other_successful();
void signal_connect::handle_change_other_fail();
void signal_connect::handle_change_status_successful();
void signal_connect::handle_change_status_fail();
