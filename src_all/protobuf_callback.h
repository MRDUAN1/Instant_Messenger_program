#pragma once
#include "person.pb.h"
#include "chatting_text.h"
#include "qmainstackwidget.h"
#include "protobuf_client.h"
#include "messages.h"
#include <functional>
#include <memory>
#include <iostream>
#include <qmessagebox.h>
class qmainstackwidget;
class chatting_text;
class widget_;
class messages;
using namespace std;
/*usr1 birthday,usr2 telphone, other_use mymaxim, usr4 image, random name*/

struct friend_information{
	string name;
	string telephone;
	string birthday;
	string mymaxim;
	string picture;
	string is_online_;
	string palace__;
	string picture_name;
};
struct _my_information{
	string name;
	string telephone;
	string birthday;
	string mymaxim;
	string picture;
	string image_name;
	string id;
};
 
class qq_main;
class protobuf_client;
class ProtobufDispatch
{
public:
	typedef std::function<int(Message_)> ProtobufMessageCallback;
	explicit ProtobufDispatch(protobuf_client *to_client, const ProtobufMessageCallback& defaultCb = default);
	
	void onProtobufMessage(Message_ message) const
	{
		
		CallbackMap::const_iterator it = callbacks_.find(message.type());
		if (it != callbacks_.end())
		{
			
			it->second(message);
		}
		else
		{
			defaultCallback_(message);
		}
	}

	void registerMessageCallback(Command_Type desc,
		const ProtobufMessageCallback& callback)
	{
		callbacks_[desc] = callback;
	}

private:
	
	
	static int findwidgetbyidandcreatechattext(int type ,string time,string id_sender, string text, string image__ = "0", string image_name_ = "0");
	void send_to_chattext(string id_sender, string text, string image__ = 0, string image_name_ = 0);
	typedef std::map<Command_Type, ProtobufMessageCallback> CallbackMap;
	static int default(Message_ message)
	{
		std::cout << "没有相关处理函数，数据包类型错误";
		return 1;
	}
	QString getCurrentDateTime();
	int image_mesage_handle(string i_mage);
	CallbackMap callbacks_;
	ProtobufMessageCallback defaultCallback_;
	static int handle_add_friend_ack(Message_ message);
	//int handle_add_friend(Message_ message);
	static int handle_register(Message_ message);
	static int handle_login(Message_ message);
	static int handle_delete_friend(Message_ message);
	static int handle_quit(Message_ message);
	static int handle_change_my_passwd(Message_ message);
	static int handle_change_other(Message_ message);
	static int handle_change_my_status(Message_ message);
	static int handle_add_friend(Message_ message);
	static int handle_change_my_name(Message_ message);
	static int handle_error(QString);
	static int handle_udp_message(Message_ message);
	static int handle_get_friend_info(Message_ message);
	static int init_friend(string friend_message__, string image_, int i = 1);
	static int handle_from_message(Message_ message);
	static int handle_not_ok(Message_ message);
	static int get_friend_address_(Message_ message);
	static int friend_login_(Message_ message);
	static int create_group_ack(Message_ message);
	static void handlelogin_group_message(string str);
	static int handle_status(Message_ message);
	static int remove_friend__(Message_ message);
	static int friend_exit_(Message_ message);
	static int exit_group_handle(Message_ message);
	static int handle_group_message(widget_ *wi, string name_, int type, string sender, string text, string imag = "0", string image_name = "0", string group_name = "0");
	static int handle_err(int i);
	static int handle_address(Message_ message);
	static int handle_camera_direct_send(Message_ message);
	static int handle_camera_direct_recv(Message_ message);
	static int handle_camera_direct_recv_ack(Message_ message);
	static int handle_camera_end(Message_ message);
	static int handle_open_file_tcp_infor(Message_ message);
	static int handle_open_file_tcp(Message_ message);
	static int handle_file_download(Message_ message);
	static int handle_file_detail(Message_ message);
	static int handle_passwd_protect(Message_ message);
	static int handle_findbackcode(Message_ message);
};


