#ifndef WIDGET_H
#define WIDGET_H

#include "chatting_text.h"
#include "toolbox.h"
#include "qmainstackwidget.h"
/*引用qmainstackwidget的全局变量protobuf_client*/
#include "detailfriendss.h"
#include <stdio.h>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QEvent>
class toolbox;
class chattext;
class detailfriendss;
class widget_ : public QFrame
{
	Q_OBJECT
public:
	explicit widget_(int posi_ = 0, QFrame *parent = 0, string id = "0");
	~widget_();
	string id__;
	int posit;
	string name;
	void set_is_group();
	void renovate_loin_exit(string id, int i);
	void set_group_member(string member);
	void set_isonline(string isonline__);
	bool if_exist;
	QPixmap pi;
	void set_message_for_chattext(int type, string time, string text_1 = "0", string image = "0", string name = "0", string id_ = "0", string name__ = "0");
	void get_image_and_text(QPixmap pix, QString text);
	void open_chattext();
	chattext *chatt;
	bool *chatisopen;
	struct hpp{
		int type; //与person里的message_type enum一致
		string text; //文字如果没有文字只有图片或者语音就为空
		string image; //图片或语音，没有为空
		string name; //图片名字
		string id;
		string name_;
		string time___;
	};
	vector<hpp>lp;
	vector<string>group_member;
protected:
	widget_*& operator =(widget_ *&);
	void contextMenuEvent(QContextMenuEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void enterEvent(QEvent * event);
	void leaveEvent(QEvent *);
	void focusInEvent(QFocusEvent *);
	void focusOutEvent(QFocusEvent *);
	void mousePressEvent(QMouseEvent *);
	public slots :
	void send_text_handle();
	void delete_handle();
	void move_balack_handle();
	void move_friend_handle();
	void move_stranger_handle();
	void detail_information_show();
	void show_group_firend_information();
	void exit_group();
private:
	QMenu *menu;
	//FILE *chat_record_file;
	//string chat_record_file_name;
	int is_context;
	QString head_image, head_image_gray;
	void clicked_me_handle();
	bool if_group;
	QLabel *mymaxim_text;
	QLabel *label_text, *label_icon;
	QAction *look_information;
	detailfriendss *_detail;
	QAction *sendtext, *delete_name, *move, *detail_information;
	int remove_friend(QString);
	QAction *move_friend, *move_stranger, *move_balack;
	toolbox *tool;
};

#endif // WIDGET_H