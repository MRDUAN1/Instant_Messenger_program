#pragma once
#include "protobuf_callback.h"
#include <qdir.h>
#include "qq_main.h"
#include "messages.h"
#include "networkn.h"
#include "toolbox.h"
#include <memory>
#include <algorithm>
#include "widget_.h"
#include "camera_modudle.h"
#include "camera_recv.h"
#include "create_group_.h"
#include <qsettings.h>
#include <process.h>
#include "look_file.h"
#include "system_tray.h"
extern system_tray *s_tt;
/***********下载*************/
extern look_file *file_dow;
extern QEvent::Type download_size;
extern QEvent::Type download_num;
extern int download_num_;
extern int download_all;
/***********下载**************/
extern int camera_file; //0摄像头，1传送文件
extern toolbox *too;
extern messages *messag;
int t;
qmainstackwidget *qmainwidget;
protobuf_client *to_client;
 _my_information my_information;
extern qq_main *me;

/*******接受文件相关信息*********/
string recv_file_name;
int recv_file_size;
sockaddr_in recv_file_sockaddr;
/*******************************/
# pragma execution_character_set("utf-8")
extern map<QString, widget_*>widges_friend;
extern map<QString, widget_*>widges_stranger;
extern map<QString, widget_*>widges_balack;
extern map<QString, widget_*>system_message;
extern map<QString, widget_*>group_message_;
extern map<QString, widget_*>widges_friend_message;
extern map<QString, widget_*>widges_stranger_mesage;
extern map<QString, widget_*>widges_balack_message;
extern map<QString, widget_*>widges_group_message;
extern networkn *net;
HANDLE send_send, send_recv, recv_send, recv_recv;
camera_recv *send_send_, *recv_send_;
camera_modudle *send_recv_, *recv_recv_;
map<string, friend_information*> friend_detail; //id为标号
/*当为注册时图片名字是与图片放在一起，当为普通消息时用专用的结构保存名字*/
void start_camera_send_send(void *)
{
	send_send_ = new camera_recv;
	send_send_->buff = "udp://234.5.6.7:3333";
	send_send_->start_();
}
void start_camera_send_recv(void *)
{
	send_recv_ = new camera_modudle;
	send_recv_->out_path = "udp://234.5.6.7:3333";
	send_recv_->start();
}
void start_camera_recv_send(void*)
{
	
	/*recv_recv_ = new camera_recv;
	recv_recv_->buff = "udp://234.5.6.7:5555";
	recv_recv_->start_();*/
	
}
void start_camera_recv_recv(void *)
{
	/*cam = new camera_modudle;
	cam->out_path = "udp://234.5.6.7:5555";
	cam->start();*/
}
ProtobufDispatch::ProtobufDispatch(protobuf_client *to_client_, const ProtobufMessageCallback& defaultCb) :defaultCallback_(defaultCb)
{
	to_client = to_client_;
	this->registerMessageCallback(add_friend, handle_add_friend);
	this->registerMessageCallback(change_my_status, handle_change_my_status);
	this->registerMessageCallback(change_my_passwd, handle_change_my_passwd);
	this->registerMessageCallback(change_my_name, handle_change_my_name);
	this->registerMessageCallback(delete_friend, handle_delete_friend);
	this->registerMessageCallback(login_respnose, handle_login);
	this->registerMessageCallback(register_request, handle_register);
	this->registerMessageCallback(add_friend_ack, handle_add_friend_ack);
	this->registerMessageCallback(get_friend_info, handle_get_friend_info);
	this->registerMessageCallback(friend_message, handle_from_message);
	this->registerMessageCallback(not_ok, handle_not_ok);
	//this->registerMessageCallback(get_friend_address, get_friend_address_);
	this->registerMessageCallback(friend_login, friend_login_);
	this->registerMessageCallback(create_group, create_group_ack);
	this->registerMessageCallback(change_friend_palace, handle_status);
	this->registerMessageCallback(remove_my_friend, remove_friend__);
	this->registerMessageCallback(friend_exit, friend_exit_);
	this->registerMessageCallback(exit_group, exit_group_handle);
	//this->registerMessageCallback(error, handle_err);
	this->registerMessageCallback(get_friend_address, handle_address);
	this->registerMessageCallback(camera_direct_send, handle_camera_direct_send);
	this->registerMessageCallback(camera_direct_recv, handle_camera_direct_recv);
	this->registerMessageCallback(camera_direct_recv_ack, handle_camera_direct_recv_ack);
	this->registerMessageCallback(camera_end, handle_camera_end);
	this->registerMessageCallback(open_file_tcp_infor, handle_open_file_tcp_infor);
	this->registerMessageCallback(file_download, handle_file_download);
	this->registerMessageCallback(file_detail, handle_file_detail);
	this->registerMessageCallback(passwd_protect, handle_passwd_protect);
	this->registerMessageCallback(findbackcode, handle_findbackcode);
	
	send_send = 0; send_recv = 0; recv_send = 0; recv_recv = 0;
	send_send_ = 0; send_recv_ = 0; recv_send_ = 0; recv_recv_ = 0;
}
int ProtobufDispatch::handle_findbackcode(Message_ message)
{
	int is_ok = message.command().is_ok();
	if (is_ok)
	{
		QMessageBox::information(NULL, "提示", "验证成功");
		string id = message.id();
		create_group_ *cg = new create_group_("重置密码", 4, 0, id);
		cg->show();
	}
	else
	{
		string wrong_message = message.command().use1();
		QMessageBox::warning(NULL, "警告", QString::fromStdString(wrong_message));
	}
	return 1;
}
int ProtobufDispatch::handle_passwd_protect(Message_ message)
{
	handle_err(40);
	return 1;
}
int ProtobufDispatch::handle_file_detail(Message_ message)
{
	int size = message.message_normal_size();
	for (int i = 0; i < size; i++)
	{
		Message_Normal normal = message.message_normal(i);
		string _file_detail_ = normal.sender();
		int pos = _file_detail_.find(' ', 0);
		string file_name____ = _file_detail_.substr(0, pos);
		string senderr = _file_detail_.substr(pos + 1);
		file_dow->insert_listwidgetitem(QString::fromStdString(senderr), QString::fromStdString(file_name____));
	}
	return 1;
}
int ProtobufDispatch::handle_file_download(Message_ message)
{
	//忘了赋值recv中的sockaddr
	if (message.command().is_ok())
	{
		recv_file_size = message.command().other_use1();
		download_all = recv_file_size;
		QApplication::sendEvent(file_dow, new QEvent(download_size));
		recv_file_sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		recv_file_sockaddr.sin_family = AF_INET;
		recv_file_sockaddr.sin_port = 6666;
		net->file_recive(1);
		
	}
	return 1;
}
int ProtobufDispatch::handle_open_file_tcp(Message_ message)
{
	net->send_file();
	return 1;
}
int ProtobufDispatch::handle_open_file_tcp_infor(Message_ message)
{
	//此id为服务器转发的对方id
	//文件服务器端口号默认为6666
	string id = message.id();
	string address = message.command().use1();
	recv_file_name = message.command().use2();
	recv_file_size = message.command().other_use1();
	
	recv_file_sockaddr.sin_addr.S_un.S_addr = inet_addr(address.data());
	recv_file_sockaddr.sin_port = 6666;
	recv_file_sockaddr.sin_family = AF_INET;
	net->file_recive();
	return 1;

}
int ProtobufDispatch::handle_camera_end(Message_ message)
{
	QMessageBox::warning(NULL, "视频结束", "对方结束了\n和您的视频通话");
	//一次只有一个匹配
	if (send_send && send_send_)
	{
		TerminateThread(send_send, 0);
		delete send_send_;
	}
	if (send_recv && send_recv_)
	{
		//TerminateThread(send_recv, 0);
		send_recv_->exit_thread = 1;
		//delete send_recv_;
	}
	if (recv_send && recv_send_)
	{
		TerminateThread(recv_send, 0);
		delete send_recv_;
	}
	if (recv_recv && recv_recv_)
	{
		//TerminateThread(recv_recv, 0);
		recv_recv_->exit_thread = 1;
		//delete recv_recv_;
	}
	return 1;
}
int ProtobufDispatch::handle_camera_direct_recv_ack(Message_ message)
{
	string id = message.id();
	string address = message.command().use1();
	int port = message.command().other_use1();
	recv_recv = (HANDLE)_beginthread(start_camera_recv_recv, 0, NULL);
	return 1;
}
int ProtobufDispatch::handle_camera_direct_recv(Message_ message)
{
	string id = message.id();
	string address = message.command().use1();
	int is_ok = message.command().is_ok();
	int port = message.command().other_use1();
	if (is_ok == 0)
	{
		QMessageBox::warning(NULL, "提示", "对方拒绝了\n您的视频聊天请求");
		return 1;
	}
	send_recv = (HANDLE)_beginthread(start_camera_send_recv, 0, NULL);
	recv_send = (HANDLE)_beginthread(start_camera_recv_send, 0, NULL);
	net->directSendFriend(address, port, 2, 0);
	return 1;
}
int ProtobufDispatch::handle_camera_direct_send(Message_ message)
{
	string request_id = message.id(); 
	string adress = message.command().use1();
	int port = message.command().other_use1();
	QString st = QString::fromStdString(request_id) + "\n请求和您视频聊天";
	QMessageBox::StandardButton button = QMessageBox::question(NULL, "视频请求", st);
	if (button == QMessageBox::StandardButton::Yes)
	{
		send_send = (HANDLE)_beginthread(start_camera_send_send, 0, NULL);
		net->directSendFriend(adress, port, 1, 1);
	}
	else
	{
		net->directSendFriend(adress, port, 1, 0);
	}
	return 1;
}
int ProtobufDispatch::handle_err(int i)
{
	if (i == 19)
		QMessageBox::warning(NULL, "警告", "对方不在线");
	else if (i == 40)
		QMessageBox::warning(NULL, "警告", "操作失败");
	return 1;
}
int ProtobufDispatch::handle_address(Message_ message)
{
	//此处错误把address在name中
	string nam = message.command().use1();
	string address = message.command().use2();
	int port = message.command().other_use1();
	int is_ok = message.command().is_ok();
	if (is_ok == 0)
	{
		handle_err(19);
	}
	else
	{
		if (camera_file == 0)
		net->directSendFriend(nam, port, 0, 0);
	}
	return 1;
}
int ProtobufDispatch::exit_group_handle(Message_ message)
{
	string o = message.command().use1();
	handle_error(QString::fromStdString(o));
	return 1;
}
int ProtobufDispatch::friend_exit_(Message_ message)
{
	string id = message.id();
	too->renovate_loin_exit(id, 0);
	return 1;
}
int ProtobufDispatch::remove_friend__(Message_ message)
{
	QMessageBox::information(NULL, "删除失败", NULL);
	return 1;
}
int ProtobufDispatch::handle_status(Message_ message)
{
	int i = message.command().is_ok();
	if (i == 1) return 1;
	else
		QMessageBox::information(NULL, "改变状态失败", "出现错误");
	return 1;
}
int ProtobufDispatch::create_group_ack(Message_ message)
{
	int i = message.command().is_ok();
	string ik = message.command().use1();
	if (i == 0)
	{
		QMessageBox::warning(NULL, "创建群组失败", QString::fromStdString(ik));
		return 1;
	}
	else
	{
		QMessageBox::information(NULL, "创建群组成功", NULL);
	}
	string name = message.command().use2();
	qmainwidget->_add_friend(ik, ik, "0", "0", "1", 4);
	return 1;
}
int ProtobufDispatch::handle_not_ok(Message_ message)
{
	Command cmd = message.command();
	QMessageBox::warning(NULL, "添加好友失败", "添加好友失败");
	return 1;
}
int ProtobufDispatch::handle_register(Message_ message)
{
	Command cmd =  message.command();
	if (cmd.is_ok())
	{
		string i_d = message.command().use1();
		QString ok_message = "恭喜您,注册成功\n注册id号为:";
		ok_message += QString::fromStdString(i_d);
		ok_message += "\n请牢记您的账号";
		QMessageBox::about(NULL, "注册信息", ok_message);
		return 0;
	}
	string wrong_reason = cmd.use1();
	QMessageBox::warning(NULL, "注册信息", QString(wrong_reason.data()));
	return 1;
}
int ProtobufDispatch::friend_login_(Message_ message)
{
	string id = message.id();
	too->renovate_loin_exit(id, 1);
	return 1;
}
int ProtobufDispatch::handle_change_my_passwd(Message_ message)
{
	Command cmd = message.command();
	if (!cmd.is_ok())
	{
		string wrong_resason = cmd.use1();
		QString str_wrong = QString::fromStdString(wrong_resason);
		QMessageBox::warning(qmainwidget, "更改密码失败", str_wrong);
		return 0;
	}
	else
	{
		QMessageBox::information(qmainwidget, "更改密码成功", NULL);
	}
	return 1;
}
int ProtobufDispatch::get_friend_address_(Message_ message)
{
	/*如果找不到对方ip则返回错误,use1返回地址,use2返回端口*/
	
	string use = message.command().use1();
	string ip_address = message.command().use2();
	int port = message.command().is_ok();
	return 1;
}
int ProtobufDispatch::handle_change_my_status(Message_ message)
{
	if (!message.command().is_ok())
	{
		string wrong_resason = message.command().use1();
		QString str_wrong = QString::fromStdString(wrong_resason);
		QMessageBox::warning(qmainwidget, "更改状态失败，请重复更改", str_wrong);
	}
	return 1;
}
int ProtobufDispatch::handle_delete_friend(Message_ message)
{
	Command cmd = message.command();
	if (!cmd.is_ok())
	{
		string wrong_resason = message.command().use1();
		QString str_wrong = QString::fromStdString(wrong_resason);
		QMessageBox::warning(qmainwidget, "删除好友失败，请重复更改", str_wrong);
	}
	else
	{
		
	}
	return 1;
}

int ProtobufDispatch::handle_quit(Message_ message)
{
	return 1;
}

int ProtobufDispatch::handle_login(Message_ message)
{
	/*糟糕的代码，冗余的代码*/
	t = 0;
	Command cmd = message.command();
	string use = cmd.use1();
	int is_ok = cmd.is_ok();
	if (!is_ok)
	{
		handle_error(QString::fromStdString(use));
		net->exit_network();
		return 0;
	}
	qmainwidget = new qmainstackwidget(to_client);
	s_tt->login_success();
	look_file *fil = new look_file;
	me->hide();
	int size = message.message_normal_size();
	//1好友2group好友0为普通消息
	for (int i = 0; i < size; i++)
	{
		Message_Normal normal = message.message_normal(i);
		/*messagetype是一个新的定义当他为0时就是消息到来不为0时就是自己或者好友的信息*/
		//1为添加好友信息
		if (normal.messagetype() == 1)
		{
			t++;
			string friendmessage = normal.sender();
			string image__ = normal.image();
			if (t == 1)
			{
				init_friend(friendmessage, image__, 1);

			}
			else
				init_friend(friendmessage,image__, 0);
		}
		else if (normal.messagetype() == 2)
		{
			string name = normal.sender();
			handlelogin_group_message(name);
		}
	else if (!normal.messagetype())
	{
		string sender = normal.sender();
		string text = normal.text();
		string imag = normal.image();
		string im_name = normal.image_name();
		string nam = normal.st_name();
		string group_name = normal.group_name();
		string time_________ = normal.time_new();
		int i = normal.type();
		if (i == 7)
		{
			if (!strcmp(text.data(), "0")) QMessageBox::information(NULL, "拒绝请求", QString("%1拒绝了您的请求").arg(QString::fromStdString(sender)));
			else QMessageBox::information(NULL, "同意请求", QString("%1同意了您的请求").arg(QString::fromStdString(sender)));
			return 1;
		}
		else if (i == 6)
		{
			Message_ message;
			Command *cmd = new Command;
			cmd->set_use1(sender);
			cmd->set_use2(text);
			cmd->set_use3(imag);
			message.set_allocated_command(cmd);
			handle_add_friend(message);
			return 1;
		}
		if (!nam.empty() && !group_name.empty())
		{
			widget_ *wi = group_message_[QString::fromStdString(group_name)];
			wi->set_message_for_chattext(i, time_________,text, imag, im_name, sender, nam);
			messag->handle_group_message(time_________,wi, nam, i, sender, text, imag, im_name, group_name);
			continue;
		}
		
		if (!strcmp(imag.data(), "0"))
		findwidgetbyidandcreatechattext(i,time_________, sender, text);
		else findwidgetbyidandcreatechattext(i, time_________, sender, text, imag, im_name);
	}
	}
	
	t = 0;
	return 1;
}
bool is_space(char c)
{
	return isspace(c);
}
void ProtobufDispatch::handlelogin_group_message(string str)
{
	//string group_name___;
	auto i = str.begin();
	auto h = std::find_if(i, str.end(), isspace);
	string group_name = string(str.begin(), h);
	friend_information *fri = new friend_information;
	fri->birthday = "0";
	fri->mymaxim = "0";
	fri->name = group_name;
	fri->picture = "0";
	fri->telephone = "0";

	friend_detail[group_name] = fri;
	qmainwidget->add_group_(group_name);
	
	string::iterator p;
	int j = 0;
	while (!((p = std::find_if(h + 1, str.end(), isspace)) == str.end()))
	{
		string name1 = string(h + 1, p);
		h = p;
		qmainwidget->LoginGroupMember(group_name ,name1);
		name1.clear();	
	}
}
/*如果i有值为自己的信息如果i没有值为他人的信息*/
int ProtobufDispatch::init_friend(string friend_message__, string _image, int i)
{
	/*冗余的代码*/
	int pos = friend_message__.find('*', 0);
	int pos_2 = friend_message__.find('*', pos + 1);
	int pos_3 = friend_message__.find('*', pos_2 + 1);
	int pos_4 = friend_message__.find('*', pos_3 + 1);
	int pos_5 = friend_message__.find('*', pos_4 + 1);
	int pos_6 = friend_message__.find('*', pos_5 + 1);
	int pos_7 = friend_message__.find('*', pos_6 + 1);
	int pos_8 = friend_message__.find('*', pos_7 + 1);
	string id___ = friend_message__.substr(0, pos);
	string name___ = friend_message__.substr(pos + 1, pos_2 - pos - 1);
	string birthday__ = friend_message__.substr(pos_2 + 1, pos_3 - pos_2 - 1);
	string telephone___ = friend_message__.substr(pos_3 + 1, pos_4 - pos_3 - 1);
	string mymaxim__ = friend_message__.substr(pos_4 + 1, pos_5 - pos_4 - 1);
	string image__ = friend_message__.substr(pos_5 + 1, pos_6 - pos_5 -1);
	image__ = _image;
	string isonline = friend_message__.substr(pos_6 + 1, pos_7 - pos_6 - 1);
	string _palace = friend_message__.substr(pos_7 + 1, pos_8 - pos_7 - 1);
	string image_name = friend_message__.substr(pos_8 + 1);
	if (i)
	{
		my_information.birthday = birthday__;
		my_information.id = id___;
		my_information.picture = image__;
		my_information.mymaxim = mymaxim__;
		my_information.telephone = telephone___;
		my_information.name = name___;
		my_information.image_name = image_name;
		qmainwidget->init_myname_mymaxim(name___, mymaxim__, image__, image_name);
		//std::shared_ptr<friend_information>fri(new friend_information);
		friend_information *fri = new friend_information;
		fri->birthday = "0";
		fri->mymaxim = "0";
		fri->name = "system";
		fri->picture = "0";
		fri->telephone = "0";

		friend_detail["system"] = fri;
		qmainwidget->_add_friend("system", "system", "0", "0", "1", 0);
		return 1;
	}
	//std::shared_ptr<friend_information>fri(new friend_information);
	friend_information *fri = new friend_information;
	fri->birthday = birthday__;
	fri->mymaxim = mymaxim__;
	fri->name = name___;
	fri->picture = image__;
	fri->picture_name = image_name;
	fri->telephone = telephone___;
	//string all_ = id_ + " " + name_ + " " + birthday_ + " " + telephone + " " + mymaxim + " " + image_ + " " + isonline_ + " " + pa;
	friend_detail[id___] = fri;
	int n = atoi(_palace.c_str());
	
	qmainwidget->_add_friend(id___, name___, image__, image_name, isonline, n);
	
	return 1;
}

int ProtobufDispatch::handle_change_other(Message_ message)
{
	return 1;
}
int ProtobufDispatch::handle_error(QString error_type)
{
	QMessageBox::warning(NULL, "错误信息", error_type);
	return 1;
}
int ProtobufDispatch::handle_udp_message(Message_ message)
{
	int size = message.message_normal_size();
	for (int i = 0; i < size; i++)
	{
		Message_Normal normal = message.message_normal(i);
		string sender = normal.sender();
		string time = normal.time();
		string text = normal.text();
		qmainwidget->message_come(sender, text, time);
	}
	return 1;
}
int ProtobufDispatch::handle_add_friend_ack(Message_ message)
{
	/*回复的信息,usr1代表同意添加的id,usr2代表名字，error代表出现错误，other_use如果不ok
	代表对方拒绝添加好友，usr3代表image*/
	Command cmd = message.command();
	if (message.type() == Command_Type::error)
	{
		handle_error("网络出现错误，请您重复添加");
	}
	int is_ok = cmd.other_use1();
	if (!is_ok)
	{
		handle_error("对方不同意您添加他为好友");
		return 0;
	}
	string _id = cmd.use1();
	string _name = cmd.use2();
	string _image = cmd.use3();
	string image_name = cmd.other_use();
	
	if (!qmainwidget)
	{
		QMessageBox::warning(NULL, "系统出错", "找不到登录信息却添加好友");
	}
	friend_information *fri = new friend_information;
	fri->picture = "0";
	fri->name = _name;
	fri->is_online_ = "0";
	fri->mymaxim = "0";
	fri->palace__ = "0";
	fri->telephone = "0";
	fri->picture_name = "0";
	friend_detail[_id] = fri;
	qmainwidget->_add_friend(_id, _name, "0", "0", "0");
	//std::shared_ptr<friend_information>fri(new friend_information);
	
	//to_client->get_friend_info_handle(_id);
	return 1;

}
int ProtobufDispatch::handle_add_friend(Message_ message)
{
	/*usr1代表请求添加好友的id,usr2代表请求添加好友的请求信息
	isok代表是否出错*/
	Command cmd =  message.command();
	string id_query_add_friend = cmd.use1();
	string query_info = cmd.use2();
	string isgroup = cmd.use3();
	qmainwidget->query_add_friend(id_query_add_friend, query_info, isgroup);
	return 1;
}
//获取好友信息
int ProtobufDispatch::handle_get_friend_info(Message_ message)
{
	//birthday, telphone, mymaxim, image, name
	string id_ = message.id();
	string birthday = message.command().use1();
	string telphone = message.command().use2();
	string mymaxim = message.command().other_use();
	string image = message.command().use3();
	string name = message.command().random_();
	std::shared_ptr<friend_information>info(new friend_information);
	info->name = name;
	info->birthday = birthday;
	info->mymaxim = mymaxim;
	info->picture = image;
	info->telephone = telphone;
	friend_detail[id_] = info.get();
	return 1;
}
int ProtobufDispatch::handle_change_my_name(Message_ message)
{
	int i = message.command().is_ok();
	if (!i)
	{
		string g = message.command().use1();
		QString str = QString::fromStdString(g);
		QMessageBox::warning(qmainwidget, "改变好友失败", str);
		return 0;
	}
	return 1;
	
		
}
int ProtobufDispatch::handle_from_message(Message_ message)
{
	string from_message_id = message.id();
	QString str = QString::fromStdString(from_message_id);
	int i = message.message_normal_size();
	if (i != 1)
	{
		QString wrong_message = "来自好友";
		wrong_message += str;
		wrong_message += "的消息异常";
		QMessageBox::warning(qmainwidget, "接收消息异常", wrong_message);
		return 0;
	}
	Message_Normal message_text = message.message_normal(0);
	string id_sender = message_text.sender();
	message_type tp = message_text.type();
	string image__ = message_text.image();
	string image_name_ = message_text.image_name();
	
	if (image__.empty())
	{
		image__.clear();
		image_name_.clear();
	}
	string text = message_text.text();
	findwidgetbyidandcreatechattext(tp, from_message_id, text, image__, image_name_);
	return 1;
}
int ProtobufDispatch::image_mesage_handle(string i_mage)
{
	QDir *temp = new QDir;
	bool exist = temp->exists("friend_picture");
	if (!exist)
		bool ok = temp->mkdir("friend_picture");
	
	string file_name__ = "friend_picture";
	file_name__.append("/");
	file_name__.append(getCurrentDateTime().toStdString());

	ofstream fd(file_name__, std::ios::out | std::ios::binary);
	fd.write(i_mage.data(), i_mage.size());
	return 1;
	
}
QString ProtobufDispatch::getCurrentDateTime()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();

	return QString("%1  %2").arg(date.toString(Qt::ISODate))
		.arg(time.toString(Qt::ISODate));
}



//通过id发现widget然后通过widget创建或者显示chattextting
int ProtobufDispatch::findwidgetbyidandcreatechattext(int type ,string time_______, string id_sender, string text, string image__, string image_name_)
{
	auto iter = widges_friend.find(QString::fromStdString(id_sender));
	if (iter == widges_friend.end())
	{
		iter = widges_stranger.find(QString::fromStdString(id_sender));
		if (iter == widges_stranger.end())
		{
			auto iter = widges_balack.find(QString::fromStdString(id_sender));
			if (iter == widges_balack.end())
			{
					QMessageBox::critical(NULL, "数据异常", NULL);
			}
			else
			{
				if (*(iter->second->chatisopen))
				{
					if (type == 2)
					{
						string np = "friend_sound/" + image_name_;
						iter->second->chatt->set_sound_file(image__, image_name_);
						iter->second->chatt->send_sound(time_______ ,1, QString::fromStdString(image_name_));
						
						return 1;
					}
					iter->second->chatt->set_messagefrom_friend(time_______ ,text, image__, image_name_);
					iter->second->set_message_for_chattext(type, time_______,text, image__, image_name_);
					iter->second->chatt->show();
				}
				else {
					iter->second->set_message_for_chattext(type, time_______, time_______, text, image__, image_name_);
					qmainwidget->message_com_set_widget(id_sender);
				}
			}
		}
		else
		{
			if (*(iter->second->chatisopen)) {
				if (type == 2)
				{
					string j = "friend_sound/" + image_name_;
					iter->second->chatt->set_sound_file(image__, image_name_);
					iter->second->chatt->send_sound(time_______ ,1, QString::fromStdString(image_name_));
					
					return 1;
				}
				iter->second->chatt->set_messagefrom_friend(time_______, text, image__, image_name_);
				iter->second->set_message_for_chattext(type, time_______, text, image__, image_name_);
				iter->second->chatt->show();
			}
			else {
				iter->second->set_message_for_chattext(type, time_______, text, image__, image_name_);
				qmainwidget->message_com_set_widget(id_sender);
			}
		}
	}
	else
	{
		if (*(iter->second->chatisopen))
		{
			if (type == 2)
			{
				string in = "friend_sound/" + image_name_;
				iter->second->chatt->set_sound_file(image__, image_name_);
				iter->second->chatt->send_sound(time_______ ,1, QString::fromStdString(image_name_));
				
				return 1;
			}
			iter->second->chatt->set_messagefrom_friend(text, image__, image_name_);
			iter->second->set_message_for_chattext(type, time_______, text, image__, image_name_);
			//widges_friend_message[QString::fromStdString(id_sender)]->lp.swap(widges_friend.find(QString::fromStdString(id_sender))->second->lp);
			
			iter->second->chatt->show();
		}
		else {
			iter->second->set_message_for_chattext(type, time_______, text, image__, image_name_);
			qmainwidget->message_com_set_widget(id_sender);
		}
	}
	return 1;
}
