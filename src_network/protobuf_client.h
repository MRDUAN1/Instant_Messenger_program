#pragma once
#include "person.pb.h"
#include "networkn.h"
#include "protobuf_callback.h"
//引入chattext原因和widget原因
#include "chatting_text.h"
#include "widget_.h"
//chatting和widget都有protobuf_client,此文件保存widget和chatting的联系，为了
#include <qstring.h>
#include <qobject.h>
#include <string>
using namespace std;
class chatting_text;
class chattext;
class networkn;
class widget_;
class newwork;

class ProtobufDispatch;

class protobuf_client :public QObject
{
	Q_OBJECT
public:
	protobuf_client();
	~protobuf_client();
	void change_passwd_one(string id, string passwd);
	void find_passwd(string id, string question, string answer);
	void change_(string, int);
	void change_passwd_name(string, string, bool is_protect = false);
	//int send_groupcreate_message(QString str);
	int query_add_friend(QString account, QString query_info);
	int make_login_message(QString, QString);
	int make_register_message(QString, QString, QString, QString, QString, string, string image_name);
	//int send_sound_message(string, string);
	int send_addfriend_agree(string id, bool ok_, string isgroup);
	int get_friend_info_handle(string id);
	int send_normal_message(string id ,string str, string image = "0", string image_name = "0", string group_name = "0");
	int send_sound_message(string this_id, string id, string sound, string group_name = "0");
	void handle_message(string data);
	void move_group(string friend_, int pos);
	//void remove_friend(string friend_);
	int quit_login___();
	void  handle_send_file(string id_, string file_name, long size);
	void handle_upload_file(string file_name, long size);
	
protected:
	QString getCurrentDateTimee();
	void customEvent(QEvent *event);
private:
	
	void protobuf_client::analyse(string data);
	string image;	


};

