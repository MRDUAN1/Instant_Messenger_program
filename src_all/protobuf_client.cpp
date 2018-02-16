#include "protobuf_client.h"
#include "qmainstackwidget.h"
#include "qq_main.h"
//#include <Windows.h>
#include <process.h>

#include <string>
#include <memory>
#include <qsettings.h>
extern qmainstackwidget *wip;
extern qq_main *me;
extern struct _my_information my_information;
string id;
string id_new;
networkn *network;
int status;
extern SOCKADDR_IN SevAddr;
extern map<string, friend_information*> friend_detail;
//map<chattext*, widget_*>chat_with_widget;
map<string, chattext*>chat_with;

ProtobufDispatch *call_back;
protobuf_client *pro;
#include <qmessagebox.h>

extern int server_listen;
static QSettings client_setting("client_config.ini", QSettings::IniFormat);
#define _SCL_SECURE_NO_WARNINGS
using namespace std;
const QEvent::Type CustomEvent_Login = (QEvent::Type)5001;
const QEvent::Type CustomEvent_Login_Udp = (QEvent::Type)5002;
const QEvent::Type CustomEvent_Information = (QEvent::Type)5003;
const QEvent::Type Server_break = (QEvent::Type)5009;
extern char buf[1024];
extern string udp_data;
extern string tcp_data;
extern string informations;
void protobuf_client::change_passwd_one(string id, string passwd)
{
	/*passwd_protect = 40;
    findbackcode = 41;*/
	Message_ message;
	message.set_id(id);
	message.set_type(passwd_change);
	Command *cmd = new Command;
	cmd->set_use1(passwd);
	message.set_allocated_command(cmd);
	string info;
	message.SerializeToString(&info);
	network->start_connect(info);
}
void protobuf_client::find_passwd(string id, string question, string answer)
{
	Message_ message;
	message.set_id(id);
	message.set_type(findbackcode);
	Command *cmd = new Command;
	cmd->set_use1(question);
	cmd->set_use2(answer);
	message.set_allocated_command(cmd);
	string info;
	message.SerializeToString(&info);
	network->start_connect(info);
}
QString protobuf_client::getCurrentDateTimee()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();

	return QString("%1  %2").arg(date.toString(Qt::ISODate))
		.arg(time.toString(Qt::ISODate));
}
//0为改变用户名,use为改变的用户名，1为删除好友，use为被删除好友的名字
//2为改变mymaxim,4为离开群组,5加入群组,6为获取好友ip地址端口号等,7退出视频聊天
//8位为download文件从服务器
void protobuf_client::change_(string str, int i)
{
	Message_ message;
	if (i == 1)
		message.set_type(remove_my_friend);
	else if (i == 0)
		message.set_type(change_my_name);
	else if (i == 2)
		message.set_type(change_mymaxim__);
	else if (i == 3)
		message.set_type(create_group);
	else if (i == 4)
		message.set_type(exit_group);
	else if (i == 5)
		message.set_type(joinGroupRequest);
	else if (i == 6)
		message.set_type(get_friend_address);
	else if (i == 7)
		message.set_type(camera_end);
	else if (i == 8)
		message.set_type(file_download);
	message.set_id(id);
	Command *cmd = new Command;
	cmd->set_use1(str);
	message.set_allocated_command(cmd);
	string info;
	message.SerializeToString(&info);
	network->write(info);
}
void protobuf_client::handle_upload_file(string file_name, long size)
{
	//忘了没有写set_type导致程序崩溃
	Message_ message;
	message.set_id(id);
	Command *cmd = new Command;
	cmd->set_use1(file_name);
	cmd->set_other_use1(size);
	message.set_allocated_command(cmd);
	message.set_type(file_upload__);
	string info;
	message.SerializeToString(&info);
	network->write(info);
}
void protobuf_client::handle_send_file(string id_, string file_name, long size)
{
	Message_ message;
	message.set_id(id);
	message.set_type(open_file_tcp);
	Command *cmd = new Command;
	cmd->set_use1(id_);
	cmd->set_use2(file_name);
	cmd->set_other_use1(size);
	message.set_allocated_command(cmd);
	string info;
	message.SerializeToString(&info);
	network->write(info);
}
void protobuf_client::change_passwd_name(string old, string ne, bool is_protect)
{
	Message_ message;
	if (!is_protect)
		message.set_type(change_my_passwd);
	else
		message.set_type(passwd_protect);
	message.set_id(id);
	Command *cmd = new Command;
	cmd->set_use1(old);
	cmd->set_use2(ne);
	string info;
	message.set_allocated_command(cmd);
	message.SerializeToString(&info);
	network->write(info);
}
int protobuf_client::quit_login___()
{
	Message_ message;
	message.set_type(quit);
	message.set_id(id);
	string info;
	message.SerializeToString(&info);
	network->write(info);

	return 1;
}
void protobuf_client::move_group(string friend_, int pos)
{
	Message_ message;
	message.set_type(change_friend_palace);
	message.set_id(id);
	Command *cmd = new Command;
	cmd->set_other_use1(pos);
	cmd->set_use1(friend_);
	message.set_allocated_command(cmd);
	string info;
	message.SerializeToString(&info);
	network->write(info);
}

void protobuf_client::customEvent(QEvent *event)
{
	
	if (event->type() == CustomEvent_Login)
	{
		
		if (tcp_data.empty()) return;
		string hp = tcp_data;
		tcp_data.clear();
		pro->handle_message(hp);
		memset(buf, 0, 1024);
		
	}
	else if (event->type() == CustomEvent_Login_Udp)
	{
		
		if (udp_data.empty())
			return;
		pro->handle_message(udp_data);
		udp_data.clear();
	}
	else if (event->type() == CustomEvent_Information)
	{
		QMessageBox::warning(NULL, "警告", QString::fromStdString(informations));
		informations.clear();
	}
	else if (event->type() == Server_break)
	{
		QMessageBox::warning(NULL, "警告", "服务器异常");
		network->exit_network();
		me->show();
		wip->quit_client();
		wip->deleteLater();
	}
}

protobuf_client::protobuf_client()
{
	call_back = new ProtobufDispatch(this);
	pro = this;
	network = new networkn;
}
protobuf_client::~protobuf_client()
{
	if (network)
		delete network;
	if (call_back)
		delete call_back;
}
int protobuf_client::make_login_message(QString _account, QString _passwd)
{
	std::string account = _account.toStdString();
	id = account;
	id_new = account;
	std::string passwd = _passwd.toStdString();
	Message_ message;
	//std::shared_ptr<Command> commad(new Command);
	Command *commad = new Command;
	message.set_allocated_command(commad);
	commad->set_use1(account);
	commad->set_use2(passwd);
	commad->set_is_ok(status);
	message.set_id(id);
	message.set_type(login_request);
	std::string query_server;
	string data;
	message.SerializeToString(&data);
	//encode_message(query_server, data);
	network->start(data, account);
	return 1;
}
int hp()
{
	return 1;
}
//此处的图片不需要用name,发送给好友的图片需要name
int protobuf_client::make_register_message(QString _account, QString _passwd, QString _birthday, QString _telphone, QString _mymaxim, string str_image, string image_name)
{
	Message_ message;
	if (_birthday.isEmpty()) _birthday = "0";
	if (_telphone.isEmpty()) _telphone = "0";
	if (_mymaxim.isEmpty()) _mymaxim = "0";
	if (str_image.empty()) str_image = "0";
	std::string account = _account.toStdString();
	std::string passwd = _passwd.toStdString();
	string birthday = _birthday.toStdString();
	string telphone = _telphone.toStdString();
	string mymaxim = _mymaxim.toStdString();
	//std::shared_ptr<Register_Request>register_query(new Register_Request);
	Register_Request *register_query = new Register_Request;
	register_query->set_name(account);
	register_query->set_code(passwd);
	register_query->set_birthday(birthday);
	register_query->set_telphone(telphone);
	register_query->set_mymaxim(mymaxim);
	if (!str_image.empty())
	{
		register_query->set_image(str_image);
		register_query->set_image_name(image_name);
	}
	message.set_allocated_register_request(register_query); 
	message.set_type(register_request);
	string query;
	string data;
	message.SerializePartialToString(&query);
	network->start_connect(query);
	return 1;
}

void protobuf_client::handle_message(string data)
{
	string hp = data;
	analyse(hp);	
}
void protobuf_client::analyse(string data)
{
	Message_ message;
	message.ParseFromString(data);
	call_back->onProtobufMessage(message);	
}
int protobuf_client::send_addfriend_agree(string id_, bool ok_, string isgroup)
{
	/*other_usr1代表是否同意添加好友如果是1代表允许添加好友,0代表不许添加好友*/
	/*usr2代表被添加人的图片,usr1代表想添加我的id,usr3代表我的id,如果不同意只有id和是否同意*/
	Message_ message;
	string info;
	Command *cmd = new Command;
	message.set_id(id);
	cmd->set_use1(id_);
	message.set_type(add_friend_ack);
	if (strcmp(isgroup.data(), "0"))
	{
		cmd->set_is_ok(1); //1group
	}
	else cmd->set_is_ok(0);
	if (ok_ == false)
	{
		cmd->set_other_use1(ok_);
		cmd->set_use3(isgroup);
		message.set_allocated_command(cmd);
		message.SerializeToString(&info);
		network->write(info);
		return 1;
	}
	//cmd->set_use2(my_information.picture);
	//cmd->set_use3(my_information.image_name);
	cmd->set_other_use(my_information.name);
	cmd->set_other_use1(ok_);
	cmd->set_use3(isgroup);
	message.set_allocated_command(cmd);
	message.SerializeToString(&info);
	network->write(info);
	return 1;
}
int protobuf_client::get_friend_info_handle(string id)
{
	Message_ message;
	string info;
	std::shared_ptr<Command>cmd(new Command);
	message.set_id(id);
	cmd->set_use1(id);
	message.SerializeToString(&info);
	network->write(info);
	return 1;
}

int protobuf_client::send_sound_message(string id1, string sound1, string na, string group_name)
{
	Message_ message;
	message.set_id(id);
	
	Message_Normal *ms = message.add_message_normal();
	if (!strcmp(group_name.data(), "0"))
		message.set_type(friend_message);
	else
	{
		message.set_type(group_message);
		ms->set_group_name(group_name);
	}
	ms->set_image(sound1);
	ms->set_time_new(getCurrentDateTimee().toStdString());
	ms->set_type(sound);
	ms->set_sender(my_information.id);
	ms->set_reciver(id1);
	ms->set_image_name(na);
	string info;
	message.SerializeToString(&info);
	network->write(info);
	return 1;
}
int protobuf_client::send_normal_message(string i_d ,string str, string image, string image_name, string isgroupname)
{
	Message_ message;
	string info;
	string text_ = str;
	Message_Normal *normal_message =  message.add_message_normal();
	if (image.empty()) image = "0";
	normal_message->set_type(normal);
	normal_message->set_sender(my_information.id);
	normal_message->set_reciver(i_d);
	normal_message->set_text(text_);
	if (strcmp(image.data(), "0"))
	{
		normal_message->set_image(image);
		normal_message->set_image_name(image_name);
	}
	normal_message->set_messagetype(message_type::normal);
	normal_message->set_time_new(getCurrentDateTimee().toStdString());
	message.set_id(id);
	if (strcmp(isgroupname.data(), "0"))
	{
		message.set_type(group_message);
		normal_message->set_group_name(isgroupname);
	}
	else
	message.set_type(friend_message);
	message.SerializeToString(&info);
	network->write(info);
	return 1;
}
int protobuf_client::query_add_friend(QString account_, QString query_info_)
{
	/*use1对方的id号，use2对方请求信息*/
	string _account = account_.toStdString();
	string query_info__ = query_info_.toStdString();
	Message_ message;
	message.set_id(my_information.id);
	message.set_type(Command_Type::add_friend);
	//std::shared_ptr<Command>type_command(new Command);
	Command *type_command = new Command;
	message.set_allocated_command(type_command);
	type_command->set_use1(_account);
	type_command->set_use2(query_info__);
	string info;
	message.SerializeToString(&info);
	network->write(info);
	return 1;
}
