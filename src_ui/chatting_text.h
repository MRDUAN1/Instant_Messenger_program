#ifndef CHATTING_H
#define CHATTING_H
/*被protobuf_callback引用*/
#include <QtWidgets/QMainWindow>
#include "ui_chatting.h"
#include "widget_.h"
#include "protobuf_client.h"
#include "tool_widget.h"
#include <qtextedit.h>
#include <qtextbrowser.h>
#include <qpushbutton.h>
#include <qpainter.h>
#include <qevent.h>
#include <qbitmap.h>
#include <qboxlayout.h>
#include <QFontDialog>
#include <qfile.h>
#include <string>
#include <qstring.h>
class widget_;
using namespace std;
class protobuf_client;
# pragma execution_character_set("utf-8")
class chattext : public QWidget
{
	Q_OBJECT
public:
	void set_file_record(FILE *);
	void if_is_group(bool if_group_, string group_name_);
	void send_sound(string time__ = "0", int i = 0, QString str = "0", string = "0", bool is_record = false, bool is_my = false);
	void set_sound_file(string ing, string nam);
	chattext(string id,protobuf_client *protob, QWidget *parent = 0);
	//record出现问题
	int set_messagefrom_friend(string time______, string text, string image = "0", string image_name = "0", string name = "0", bool is_record = false, bool is_my = false);
	//void message_text_sound_come(string sound_message);
	~chattext();
public slots:
	void front_trigger();
	void look_trigger();
	void picture_trigger();
	void sound_trigger();
	void sound_top_trigger();
	void camera_trigger();
	void send_file_trigger();
	void chatroom_trigger();
	void send_message_handle();
	void handle_send_image(string hp = "0");
	void handle_sound(const QUrl);
	void close_widget();
	void handle_camera_end();
	void handle_click_record();
	void grap_picture_();
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	void create_button();
	void set_button();
	void layout_button();
	void set_connect();
	
private:
	void send_pictures(QString file);
	Ui::chattingClass ui;
	//void insert_sound_button();
	QPoint windowPos, mousePos, dPos;
	void get_my_information();
	tool_widget *tool;
	bool if_group;
	string group_name;
	QImage image_;
	string str_;
	
	bool if_speech;
	widget_ *wj;
	FILE *file_record;
	protobuf_client *protobuf_;
	QTextBrowser *textedit;
	QTextEdit	*textedit_input;
	QPushButton *front, *look, *picture, *sound, *sound_top, *camera, *send_file, *chatroom, *camera_end, *grap_picture;
	QPushButton *send_message, *close_button;
	QPushButton *image_head, *hp;
	QFontDialog *fontDialog;
	QString file;
	QString send__file;
	bool is_image;
	QUrl uri;
	QLabel *name_, *mymaxim_;
	QString getCurrentDateTime();
	
	//0为自己发送的消息1为他人发送的消息
	
	//0为自己播放，1为好友声音
	void play_sound(QString str, int i);
	string this_id;
	
		struct _friend_information{
			string name;
			string telephone;
			string birthday;
			string mymaxim;
			string picture;
			string is_online_;
			string palace__;
		}_information;
		
};

#endif // CHATTING_H
