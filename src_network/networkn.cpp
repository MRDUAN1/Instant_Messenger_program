
#include "common\initsock.h"
#include "networkn.h"
#include "chatting_text.h"
#include "person.pb.h"
#include <qfile.h>
#include <QFileInfo>
#include <process.h>
#include <qthread.h>
#include <qtimer.h>
#include <time.h>
#include <qmessagebox.h>
#include <stdlib.h>
#include <stdio.h>
#include <qprogressbar.h>
#include "look_file.h"
static bool isok;
static int progress;
extern int now_num;
static int server_num = 3;

extern qmainstackwidget *wip;
/******************下载***************************************/
extern look_file *file_dow;
extern QEvent::Type download_size;
extern QEvent::Type download_num;
extern int download_num_;
extern int download_all;
/******************************************************/
/********************上传****************************************/
extern QEvent::Type upload_size;
extern QEvent::Type upload_num;
extern int upload_num_;
extern int upload_all;
/*******************************************************************/
string start_data; //tcp的发送消息
char buff[20];
QTimer *timer1;
string informations;
extern QProgressBar *ba;
/****************************/
extern string file_download_name;
/***************************/
/***********发送文件信息*************/
extern string send_tcp_file_name;
extern long size_;
/***********************************/
/*******接受文件相关信息*********/
extern string recv_file_name;
extern int recv_file_size;
extern sockaddr_in recv_file_sockaddr;
/*******************************/
extern const QEvent::Type CustomEvent_Login = (QEvent::Type)5001;
extern const QEvent::Type CustomEvent_Login_Udp = (QEvent::Type)5002;
extern const QEvent::Type CustomEvent_Information = (QEvent::Type)5003;
extern const QEvent::Type Server_break = (QEvent::Type)5009;
extern string id;
int udp_port;
extern struct _my_information my_information;
extern map<string, friend_information*> friend_detail;
CInitSock cli;
int udp_socket;
HANDLE SOCK;
networkn *net;
//int sock;
SOCKADDR_IN SevAddr;
SOCKADDR_IN SevAddr1;
extern protobuf_client *pro;
event_base* base;
int server_listen;
int k;
struct bufferevent *p_event;
struct timeval tv;
char buf[5000];
string udp_data;
string tcp_data;
static int hp = 1;
extern bool recv_flag, send_flag;
//服务器send客户端recv
void recv_file_(void *i)
{
	string file_name__;
	file_name__ = "friend_message_image/";
	if (i == NULL)
	{
		file_name__.append(recv_file_name.data());
	}
	else
	{
		file_name__.append(file_download_name);
	}
	progress = 0;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int b = 1024 * 20;
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *)&b, sizeof(b));
	if (-1 == connect(sock, (struct sockaddr*)&recv_file_sockaddr, sizeof(sockaddr_in)))
	{
		printf("Connetc Error\n");
		exit(0);
	}
	ofstream fd(file_name__, std::ios::out | std::ios::binary);
	char buf[1024 * 20] = { '\0' };
	while (recv_file_size > 0)
	{
		int j = recv(sock, buf, 1024 * 20, 0);
		download_num_ = 0;
		recv_file_size = recv_file_size - j;
		fd.write(buf, j);
		if (i != NULL)
		{
			Sleep(1);
			download_num_ = j;
			now_num += download_num_;
			//progress += j;
			QApplication::postEvent(file_dow, new QEvent(download_num));
			//ba->setValue(progress);
		}
		memset(buf, '\0', 1024 * 20);
	}
	fd.close();
	recv_file_name.clear();
	recv_file_size = 0;
	memset((void*)&recv_file_sockaddr, '\0', sizeof(sockaddr_in));
	closesocket(sock);
}
void send_file_(void *)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int i = 1024 * 20;
	int h = 1;
	
	
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&h, sizeof(h));
	/*************崩溃后绑定******************/
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&h, sizeof(h));
	SOCKADDR_IN addrSrv;//存放本地地址信息的
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htol将主机字节序long型转换为网络字节序
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = 6666;//htos用来将端口转换成字符，1024以上的数字即可
	int ir = ::bind(sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	listen(sock, 2);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	int sock_accept = accept(sock, (sockaddr*)&addrClient, &len);
	int hj = WSAGetLastError();
	QFileInfo info;
	QString s_tr;
	info = QFileInfo(QString::fromStdString(send_tcp_file_name));
	s_tr = info.fileName();
	upload_all = info.size();
	QApplication::postEvent(wip, new QEvent(upload_size));

	
	FILE *f = fopen(send_tcp_file_name.data(), "rb+");
	char buf_[1024 * 20] = { '\0' };
	upload_num_ = 0;
	while (!feof(f))
	{
		int len_ = fread(buf_, 1, 1024 * 20, f);
		send(sock_accept, buf_, len_, 0);
		Sleep(1);
		upload_num_ += len_;
		QApplication::postEvent(wip, new QEvent(upload_num));
		memset(buf_, '\0', 1024);
	}
	upload_num_ = 0;
	upload_all = 0;
	fclose(f);
	closesocket(sock);
	closesocket(sock_accept);
	send_flag = false;
}
void networkn::file_recive(int i)
{
	if (i == 0)
	_beginthread(recv_file_, 0, NULL);
	else _beginthread(recv_file_, 0, &hp);
}
void networkn::send_file()
{
	_beginthread(send_file_, 0, NULL);
}
void networkn::udp_ack_()
{
	string heat;
	Message_ message;
	message.set_type(heart);
	Command *cmd = new Command;
	cmd->set_use1(id);
	message.set_id(id);
	message.set_allocated_command(cmd);
	message.SerializeToString(&heat);
	server_num--;
	if (server_num < 0)
	{
		QApplication::sendEvent(pro, new QEvent(Server_break));
		
	}
	int y = sendto(udp_socket, heat.data(), heat.size(), 0, (sockaddr*)&SevAddr, sizeof(sockaddr_in));
}
void networkn::read_event(struct bufferevent *bev, void *ct){
	memset(buf, '\0', 5000);
	int n = bufferevent_read(bev, buf, 4096);
	tcp_data.append(buf, n);
	if (n == 4096)
	{
		k++;
		if (k == 1) Sleep(100);
	}
	else
	{
		if (tcp_data.size())
		{
			QApplication::postEvent(pro, new QEvent(CustomEvent_Login));
			k = 0;
			
		}
	}
}
void networkn::exit_network()
{
	if (isok)
	{
		event_base_loopbreak(base);
		isok = false;
	}
	timer1->stop();
	udp_socket = 0;
	//此处出现错误
	//timer1->stop();
}
//0为发送视频视频,1为发送视频recv
void networkn::directSendFriend(string address, int port, int type, int is_ok)
{
	Message_ message;
	if (type == 0)
		message.set_type(camera_direct_send);
	else if (type == 1)
		message.set_type(camera_direct_recv);
	else if (type == 2)
		message.set_type(camera_direct_recv_ack);
	message.set_id(id);
	string info;
	Command *cmd = new Command;
	cmd->set_use1(buff);
	cmd->set_other_use1(udp_port);
	cmd->set_is_ok(is_ok);
	message.set_allocated_command(cmd);
	message.SerializeToString(&info);
	//string如果最后为0遇0截止
	//string in1 = "begin_end\0";
	
	char buffer[10] = { '\0' };
	memcpy(buffer, "begin_end", 9);
	string inl; inl.append(buffer, 10);
	string ini = inl + info;
	SOCKADDR_IN in = { '\0' };
	
	char buf[20] = { '\0' };
	memcpy(buf, address.data(), address.size());
	in.sin_addr.s_addr = inet_addr(buf);
	in.sin_port = port;
	in.sin_family = AF_INET;
	//不细心不细心不细心
	int y = sendto(udp_socket, ini.data(), ini.size(), 0, (sockaddr*)&in, sizeof(sockaddr_in));
	//this->write(info);
	int idd = WSAGetLastError();
	return;
}
void networkn::write(string data)
{
	long i = data.size();
	char buf[10] = { '\0' };
	ltoa(i, buf, 10);
	string al; al.append(buf, 10);
	al.append(data);
	start_data = al;
	if (!isok) _beginthread(init_tcp_socket, 0, (char*)data.data());
	int l = send(server_listen, al.data(), al.size(), 0);
	data.clear();
	//太他妈傻逼了
	//start_data.clear();
}

void error_event(struct bufferevent *bev, short events, void*ctx)
{
	if (events == 128) isok = true;
	else if (events != 128)
	{
		event_base_loopbreak(base);
		
		isok = false;	
	}
}
void networkn::init_tcp_socket(void *data)
{

	SevAddr.sin_addr.s_addr = inet_addr(buff);
	SevAddr.sin_family = AF_INET;
	SevAddr.sin_port = htons(4567);
	server_listen = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_listen_socket_reuseable(server_listen);
	int j = ::connect(server_listen, (sockaddr*)&SevAddr, sizeof(sockaddr));
	if (j < 0)
	{
		informations = "connect连接失败\n服务器可能未开启";
		udp_socket = 0;
		timer1->stop();
		QApplication::postEvent(pro, new QEvent(CustomEvent_Information));
		return;
	}
	//evutil_make_socket_nonblocking(server_listen);
	base = event_base_new();
	p_event = bufferevent_socket_new(base, server_listen, BEV_OPT_CLOSE_ON_FREE );
	
	evthread_use_windows_threads();
	evthread_make_base_notifiable((event_base *)base);
	//if (sock < 0) exit(0);
	bufferevent_setcb(p_event, read_event, NULL, error_event, (void*)p_event);
	bufferevent_enable(p_event, EV_READ | EV_WRITE);
	char *hp = (char*)data;
	int i = strlen(hp);
	send(server_listen, start_data.data(), start_data.size(), 0);
	start_data.clear();
	//timer();
	isok = true;
	event_base_dispatch(base);
	isok = false;
	return ;

}
void networkn::handle_udp_message(string data)
{
	int i = 1024 * 1024;
	Message_ message;
		
	if (data.empty()) return;
	//setsockopt(udp_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&i, sizeof(int));
	message.ParseFromString(data);
	if (message.type() == Command_Type::friend_message)
	{
		Message_ message_return;
		message_return.set_type(Command_Type::udp_ack);
		message_return.set_id(id);
		Command *cmd = new Command;
		string random = message.command().random_();
		if (random.empty()) return;
		cmd->set_random_(random);
		message_return.set_allocated_command(cmd);
		string data_ack;
		message_return.SerializeToString(&data_ack);
		
		sendto(udp_socket, data_ack.data(), data_ack.size(), 0, (sockaddr*)&SevAddr, sizeof(sockaddr_in));
		
	}
	else if (message.type() == Command_Type::heat_ack)
	{
		server_num++;
	}
   	udp_data = data;
	
	if (!data.empty())
		QApplication::postEvent(pro, new QEvent(CustomEvent_Login_Udp));
	
}
void networkn::recvfromclient(void*)
{
	//QMessageBox::warning(ser, "hghfg", "dhfhgf");
	char heat[1024] = { '\0' };
	string data;
	int p = 0;
	int addrlen = sizeof(sockaddr);
	sockaddr_in inn;
	while (1)
	{
		//笨蛋这么低级错误sevaddr在接受一次已经被覆盖
		int n = recvfrom(udp_socket, heat, 1024, 0, (struct sockaddr*)&inn, &addrlen);
		if (n < 0) break;
		string al(heat, heat + 10);
		if (!strcmp(al.data(), "begin"))
		{
			data.append(heat + 10, n - 10);
			memset(heat, '\0', 1024);
			continue;
		}
		else if (!strcmp(al.data(), "end"))
		{
			data.append(heat + 10, n - 10);
			memset(heat, '\0', 1024);
			goto hello;
		}
		else if (!strcmp(al.data(), "begin_end"))
		{
			data.append(heat + 10, n - 10);
			memset(heat, '\0', 1024);
			goto hello;
		}
		else
		{
			data.append(heat, n);
			memset(heat, '\0', 1024);
			continue;
		}
		hello:
		int i = WSAGetLastError();
		net->handle_udp_message(data);
		data.clear();
	}
}
int init_udp_socket()
{
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int flag = 1;
	setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag));
	char hostname[128] = { '\0' };
	gethostname(hostname, 128);
	hostent *temp;
	temp = gethostbyname(hostname);
	memset(buff, '\0', 20);
	strcpy(buff, inet_ntoa(*(struct in_addr*)(temp->h_addr_list[0])));
	//memset(&SevAddr1, 0, sizeof(sockaddr_in));
	SevAddr.sin_addr.s_addr = inet_addr(buff);
	
	SevAddr.sin_family = AF_INET;
	SevAddr.sin_port = htons(4567);
	SevAddr1.sin_addr.s_addr = inet_addr(buff);
	SevAddr1.sin_family = AF_INET;
	srand(time(0));
	udp_port = rand() % 9000 + 2000;
	SevAddr1.sin_port = udp_port;
	int fi = ::bind(udp_socket, (sockaddr*)&SevAddr1, sizeof(sockaddr_in));
	int hh = WSAGetLastError();
	int i = 1024 * 1024;
	setsockopt(udp_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&i, sizeof(i));
	setsockopt(udp_socket, SOL_SOCKET, SO_SNDBUF, (const char*)&i, sizeof(i));
	return 1;
}
void networkn::begin_thread(void *)
{
	
	
}
void networkn::start_connect(string data)
{
	int sockk = socket(AF_INET, SOCK_STREAM, 0);
	SevAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	SevAddr.sin_family = AF_INET;
	SevAddr.sin_port = htons(4567);
	
	int hp = ::connect(sockk, (struct sockaddr *)&SevAddr, sizeof(struct sockaddr_in));
	char buff[10] = { '\0' };
	char buf[1024 * 1024 * 2] = { '\0' };
	itoa(data.size(), buff, 10);
	string al; al.append(buff, 10);
	al.append(data.data(), data.size());
	int i = send(sockk, al.data(), al.size(), 0);
	
	recv(sockk, buf, 1024, 0);
	if (strlen(buf))
	
	pro->handle_message(buf);
	closesocket(sockk);

}
void networkn::start(string data, string data_1)
{
	long i = data.size();
	char buf[10] = { '\0' };
	ltoa(i, buf, 10);
	string al; al.append(buf, 10);
	al.append(data);
	start_data = al;
	init_udp_socket();
	SOCK = (HANDLE)_beginthread(init_tcp_socket, 0, (char*)data.data());
	
	
	timer1 = new QTimer();
	timer1->setInterval(3000);
	timer1->start();
	QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(udp_ack_()));
	int hStdOut = _beginthread(recvfromclient, 0, NULL);
	//if (!isok) SOCK = (HANDLE)_beginthread(init_tcp_socket, 0, NULL);
	
}
networkn::networkn()
{
	k = 0;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	net = this;
	memset(buf, 0, 1024);
	begin_thread(NULL);
	//QObject::connect(this, SIGNAL(make_message(string)), pro, SLOT(protobuf_client::handle_message(string)));
	
}


networkn::~networkn()
{
}
