#ifndef QMAINSTACKWIDGET_H
#define QMAINSTACKWIDGET_H
#include "ui_qmainstackwidget.h"
#include "toolbox.h"
#include "messages.h"
#include "widget_.h"
#include "protobuf_client.h"
#include "change_passwd_dialog.h"
#include <QtWidgets/QMainWindow>
#include <qpainter.h>
#include <qbitmap.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qrect.h>
#include <qstackedwidget.h>
#include <qpoint.h>
#include <qevent.h>
#include <qcolor.h>
#include <qicon.h>
#include <qlineedit.h>
#include <qpixmap.h>
#include <qrgb.h>
#include <string>
#include <fstream>
#include <qpixmap.h>
#include <qtextedit.h>
#include <qprogressbar.h>
# pragma execution_character_set("utf-8")
class widget_;
class messages;
class protobuf_client;
using namespace std;
class toolbox;
static protobuf_client *client__;
/*保存的全部是name*/
/*在toolbox中被引用*/

class qmainstackwidget : public QWidget
{
	Q_OBJECT

public:
	qmainstackwidget(protobuf_client *to ,QWidget *parent = 0);
	~qmainstackwidget();
	void addstackwidget();
	void quit_client();
	void file_information(string);
	void add_group_(string name);
	void set_layout_putton();
	void set_editsearch();
	void LoginGroupMember(string group_name_, string member);
	int _add_friend(string id, string name, string image__, string image_name, string isonlline, int place = 4);
	void remove_friend(int posi, QString name);
	void message_come(string sender, string text, string time);
	void query_add_friend(string query_friend, string friend_info, string isgroup);
	int remove_friend(QString name);
	void init_myname_mymaxim(string name, string mymaxim, string image = "0", string image_name = "0");

	void message_com_set_widget(string sender);
	void message_from_system(string data);
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void customEvent(QEvent *event);
public slots:
	void setwidget_message();
	void setwidget_people();
	void setwidget_other();
	void add_friend_handle();
	void create_group____();
	void quit_login_();
	void _change_use_name();
	void change_passwd_name();
	void change_mymaxim_();
	void change_maxim();
	void file_show();
	void system_setting_();
	void handle_upload_file();
	void handle_protect_code();
private:
	Ui::qmainstackwidgetClass ui;
	void create_setting_action();
	QImage toGray(QImage image);
	void setconnect();
	QPushButton *message;
	QPushButton *people;
	QPushButton *other;
	QStackedWidget *stackwidget;
	QHBoxLayout *hlayout;
	QVBoxLayout *vboxlayout;
	toolbox *box_people;
	messages *box_message;// *box_other;
	QPoint windowPos, mousePos, dPos;
	QLineEdit *edit_search;
	//新添加的
	QPixmap pix;
	QLabel *my_image_head;
	QPushButton *setting;
	QPushButton *button_name;
	QMenu *men;
	QLineEdit *button_joingroup;
	QPushButton *add_friend;
	QPushButton *create_group;
	QPushButton *quit_button;
	
	QPushButton *change_use_name, *change_the_passwd, *change_joingroup;
	QWidget *widget___;
	QAction *file, *system_setting, *upload_file, *set_protect_code;
	QProgressBar *bar;
	int num_all;
};

#endif // QMAINSTACKWIDGET_H
